#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

const int ladders[8][2] = {
    {3, 22}, {5, 8}, {11, 26}, {20, 29},
    {27, 83}, {21, 82}, {43, 77}, {50, 91}
};

const int snakes[8][2] = {
    {17, 4}, {19, 7}, {21, 9}, {62, 18},
    {54, 34}, {64, 60}, {87, 24}, {98, 79}
};

// Linked List Node
struct Cell {
    int pos;
    string cellContent;
    Cell* next;
};

// Function to create a new cell
Cell* createCell(int pos, const string& content) {
    Cell* newCell = new Cell;
    newCell->pos = pos;
    newCell->cellContent = content;
    newCell->next = nullptr;
    return newCell;
}

// Function to insert a cell at the end of the linked list
void insertCell(Cell*& head, int pos, const string& content) {
    Cell* newCell = createCell(pos, content);
    if (!head) {
        head = newCell;
        return;
    }
    Cell* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newCell;
}

// Function to search for a player, ladder, or snake in the linked list
string getCellContent(int pos, int players[], string names[], int numPlayers) {
    // Check for player
    for (int p = 0; p < numPlayers; p++) {
        if (players[p] == pos) {
            return names[p].substr(0, 2); // Player's initials
        }
    }
    // Check for ladder or snake
    for (int i = 0; i < 8; i++) {
        if (ladders[i][0] == pos) {
            return "L(" + to_string(ladders[i][1]) + ")";
        }
        if (snakes[i][0] == pos) {
            return "S(" + to_string(snakes[i][1]) + ")";
        }
    }
    return to_string(pos); // Default return value if no player, ladder, or snake
}

// Function to draw the board using linked list
void drawBoard(int players[], string names[], int numPlayers) {
    const int cellsPerRow = 10;
    const int totalWidth = cellsPerRow * 8 + 2;

    cout << "\n\n\t\t📦 Game Board (L(n)=Ladder to n, S(n)=Snake to n):\n";
    for (int i = 0; i < totalWidth; ++i) cout << "=";
    cout << endl;

    for (int row = 9; row >= 0; row--) {
        cout << "||";

        Cell* rowStart = nullptr;
        int colStart = (row % 2 == 0) ? 1 : 10;
        int colEnd = (row % 2 == 0) ? 10 : 1;
        int colIncrement = (row % 2 == 0) ? 1 : -1;

        // Create linked list for this row
        for (int col = colStart; col != colEnd + colIncrement; col += colIncrement) {
            int pos = row * 10 + col;
            string cellContent = getCellContent(pos, players, names, numPlayers);
            insertCell(rowStart, pos, cellContent);
        }

        // Output the row
        Cell* temp = rowStart;
        while (temp) {
            cout << setw(8) << temp->cellContent;
            temp = temp->next;
        }

        cout << "||\n";

        // Free memory for the row
        while (rowStart) {
            Cell* temp = rowStart;
            rowStart = rowStart->next;
            delete temp;
        }
    }

    for (int i = 0; i < totalWidth; ++i) cout << "=";
    cout << endl;
}

// Function to roll the dice
int rollDice() {
    return rand() % 6 + 1;
}

void playGame(int numPlayers) {
    int players[4] = {1, 1, 1, 1}; // Positions of up to 4 players
    string names[4];

    for (int i = 0; i < numPlayers; i++) {
        cout << "\n\t\tEnter Player " << i + 1 << " name: ";
        cin >> names[i];
    }

    srand(time(0));

    int currentPlayer = 0;
    while (true) {
        drawBoard(players, names, numPlayers);

        cout << "\n\n\t\t" << names[currentPlayer] << "'s turn. Press Enter to roll dice...";
        cin.ignore();
        cin.get();

        cout << "\n\t\tRolling Dice for " << names[currentPlayer] << "........\n";
        int roll = rollDice();

        cout << "\n\t\t" << names[currentPlayer] << " rolled a " << roll << "!\n";
        players[currentPlayer] += roll;
        if (players[currentPlayer] > 100) players[currentPlayer] = 100;

        for (int i = 0; i < 8; i++) {
            if (ladders[i][0] == players[currentPlayer]) {
                cout << "\n\t\t🎉 " << names[currentPlayer] << " climbed a ladder to " << ladders[i][1] << "!\n";
                players[currentPlayer] = ladders[i][1];
                break;
            } else if (snakes[i][0] == players[currentPlayer]) {
                cout << "\n\t\t🐍 " << names[currentPlayer] << " got bitten by a snake to " << snakes[i][1] << "!\n";
                players[currentPlayer] = snakes[i][1];
                break;
            }
        }

        if (players[currentPlayer] >= 100) {
            drawBoard(players, names, numPlayers);
            cout << "\n🏆 " << names[currentPlayer] << " wins the game!\n";
            break;
        }

        currentPlayer = (currentPlayer + 1) % numPlayers; // Rotate turn
    }
}

void StartG2() {
    int mode;
    cout << "\n\n \n\t\t🎮 Welcome to Snake & Ladder Game!\n";
    cout << "\n\t\t0. Exit Game\n";
    cout << "\n\t\t1. Single Player\n";
    cout << "\n\t\t2. Player vs Player\n";
    cout << "\n\t\t3. Player vs Player (3 Players)\n";
    cout << "\n\t\t4. Player vs Player (4 Players)\n";
    cout << "\n\t\tChoose mode (0-4): ";
    cin >> mode;
    cin.ignore(); // consume leftover newline
    
    if (mode == 0) {
        cout << "\nExiting Snake & Ladder Game. Goodbye!\n";
        return; // return to main menu if inside a function like StartG2()
    }
    else if (mode == 1)
        playGame(1); // Single Player
    else if (mode == 2)
        playGame(2); // 2 Players
    else if (mode == 3)
        playGame(3); // 3 Players
    else if (mode == 4)
        playGame(4); // 4 Players
    else
        cout << "\nInvalid choice! Please select between 0 to 4.\n";
                    
}
