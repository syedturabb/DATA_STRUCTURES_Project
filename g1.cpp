#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

const int SIZE = 5;

struct Cell {
    int row, col;
    Cell* next;
};

struct Player {
    string name;
    int score = 0;
    bool usedPower = false;
    bool hasDefusalKit = true;
    bool skipNextTurn = false;
};

void addRevealed(Cell*& head, int r, int c) {
    Cell* newCell = new Cell{r, c, nullptr};
    if (!head) head = newCell;
    else {
        Cell* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newCell;
    }
}

bool isRevealed(Cell* head, int r, int c) {
    Cell* temp = head;
    while (temp) {
        if (temp->row == r && temp->col == c) return true;
        temp = temp->next;
    }
    return false;
}

void printGrid(char grid[SIZE][SIZE], Cell* revealed) {
    cout << "\n  ";
    for (int i = 0; i < SIZE; ++i) cout << i << " ";
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < SIZE; ++j) {
            if (isRevealed(revealed, i, j)) {
                if (grid[i][j] == 'M') cout << "\033[31mM \033[0m";
                else cout << "\033[32mP \033[0m";
            } else cout << "- ";
        }
        cout << "\n";
    }
}

void placeMines(char grid[SIZE][SIZE], int mineCount) {
    int placed = 0;
    while (placed < mineCount) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (grid[r][c] != 'M') {
            grid[r][c] = 'M';
            placed++;
        }
    }
}

bool isValid(int r, int c, Cell* revealed) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && !isRevealed(revealed, r, c);
}

void usePowerUp(Player& player, char grid[SIZE][SIZE], Cell* revealed) {
    if (player.usedPower) {
        cout << "\n\t\t\tPower already used!\n";
        return;
    }
    int choice;
    cout << "\n\t\t\tChoose Power-Up:\n\n\t\t\t1. Reveal Safe Cell\n\n\t\t\t2. Skip Opponent's Turn\n\n\t\t\tChoice: ";
    cin >> choice;
    if (choice == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] != 'M' && !isRevealed(revealed, i, j)) {
                    addRevealed(revealed, i, j);
                    player.score++;
                    cout << "\n\t\t\t\033[32mSafe Cell [" << i << "," << j << "] revealed!\033[0m\n";
                    player.usedPower = true;
                    return;
                }
            }
        }
    } else if (choice == 2) {
        player.skipNextTurn = true;
        player.usedPower = true;
        cout << "\n\t\t\tOpponent's next turn will be skipped!\n";
    }
}

void gameLoop(char grid[SIZE][SIZE], bool vsComputer, int mineCount) {
    Cell* revealed = nullptr;
    int totalSafe = SIZE * SIZE - mineCount;

    Player p1, p2;
    cout << "\n\t\t\tEnter Player 1 Name: ";
    cin >> p1.name;
    if (vsComputer) p2.name = "Computer";
    else {
        cout << "\n\t\t\tEnter Player 2 Name: ";
        cin >> p2.name;
    }

    bool player1Turn = true;

    while ((p1.score + p2.score) < totalSafe) {
        printGrid(grid, revealed);
        cout <<"\n\t\t\t"<< p1.name << "'s Score: " << p1.score << " | " << p2.name << "'s Score: " << p2.score << "\n";

        Player& current = player1Turn ? p1 : p2;
        Player& opponent = player1Turn ? p2 : p1;

        if (current.skipNextTurn) {
            cout <<"\n\t\t\t"<< current.name << "'s turn is skipped due to Power-Up!\n";
            current.skipNextTurn = false;
            player1Turn = !player1Turn;
            continue;
        }

        int r, c;
        if (vsComputer && !player1Turn) {
            do {
                r = rand() % SIZE;
                c = rand() % SIZE;
            } while (!isValid(r, c, revealed));
            cout << "\n\t\t\tComputer chose: " << r << " " << c << "\n";
        } else {
            cout <<"\n\t\t\t"<< current.name << "'s turn. Enter row and column (0-" << SIZE - 1 << "): ";
            cin >> r >> c;
            if (!isValid(r, c, revealed)) {
                cout << "\n\t\t\tInvalid or already revealed. Try again.\n";
                continue;
            }
            char power;
            cout << "\n\t\t\tDo you want to use your Power-Up (y/n)? ";
            cin >> power;
            if (power == 'y' || power == 'Y') usePowerUp(current, grid, revealed);
        }

        if (!isValid(r, c, revealed)) continue;

        addRevealed(revealed, r, c);
        if (grid[r][c] == 'M') {
            if (current.hasDefusalKit) {
                cout << "\n\t\t\t\033[33mMine hit! But you used the Defusal Kit.\033[0m\n";
                current.hasDefusalKit = false;
            } else {
                cout << "\n\t\t\t\033[31mBOOM! " << current.name << " stepped on a mine.\033[0m\n";
            }
        } else {
            cout << "\n\t\t\t\033[32mSafe! Point earned.\033[0m\n";
            current.score++;
        }

        player1Turn = !player1Turn;
    }

    printGrid(grid, revealed);
    cout << "\n\n\t\t\tFinal Scores:\n" << p1.name << ": " << p1.score << "\n" << p2.name << ": " << p2.score << "\n";
    if (p1.score > p2.score)
        cout << "\033[32m" << p1.name << "\n\t\t\tWins!\033[0m\n";
    else if (p1.score < p2.score)
        cout << "\033[32m" << p2.name << "\n\t\t\t Wins!\033[0m\n";
    else
        cout << "\n\t\t\tIt's a tie!\n";
}

void StartG1() {
    srand(time(0));
    cout << "\n\n\n\t\t\t==== MINES GAME ====" << endl;
    cout << "\n\t\t\tSelect Difficulty: \n";
    cout << "\n\t\t\t 1. Easy (5 Mines)";
    cout << "\n\n\t\t\t 2. Medium (15 Mines)";
    cout << "\n\n\t\t\t 3. Hard (20 Mines)";
    cout << "\n\n\t\t\t 0. Exit Game";
    cout << "\n\n\t\t\tChoice: ";
    int choice;
    cin >> choice;
    if(choice==0) return;
    int mines = 5;
    if (choice == 2) mines = 15;
    else if (choice == 3) mines = 20;

    cout << "\n\t\t\tPlay vs:\n\n\t\t\t1. Player\n\n\t\t\t2. Computer\n\n\t\t\tChoice: ";
    int mode;
    cin >> mode;

    char grid[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            grid[i][j] = ' ';

    placeMines(grid, mines);
    gameLoop(grid, mode == 2, mines);
}