#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>  // for sleep()
using namespace std;

// Define the GameState structure to encapsulate game data
struct GameState {
    int bat_score = 0;
    int bowl_score = 0;
    int count = 0;
    int count1 = 0;
    int player_score = 0;
    int freya_score = 0;
    char player_choice;
    char freya_choice;
};

void total(int player, int freya);
void decision(char alphabet, GameState &game);
int bat(GameState &game);
int bowl(GameState &game);
int head(GameState &game);

void StartG3() {
    int choice;
    cout << "\n\n\n";
    cout << "\t\t\t===== HEAD & TAIL GAME MENU =====\n";
    cout << "\n";
    cout << "\t\t\t1. Play Game\n";
    cout << "\n";
    cout << "\t\t\t0. Exit\n";
    cout << "\n";
    cout << "\t\t\tEnter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        GameState game;
        head(game); // Start the game
    }
    else if (choice == 0) {
        cout << "Exiting game... Goodbye!\n";
        return; // return from the current function
    }
    else {
        cout << "Invalid choice! Please enter 0 or 1.\n";
    }
    
}

int head(GameState &game) {
    char toss;
    cout << ".....................Welcome to Head/Tail Game!.....................\n";
    cout << "Rules:\n1: The limit for score is 6. Breaking this rule will lead to exit of the program.\n";
    cout << "2: Do as you're instructed, pressing any other keys will lead to the exit of the game and program.\n";
    cout << "You can play this game only once.\n*Follow the Rules!\n*Have Fun\n";
    cout << "\nPress H for Head\nPress T for Tail\n";

    cin >> toss;

    if (toss == 'H' || toss == 'h' || toss == 't' || toss == 'T') {
        game.player_choice = toss;
        if (toss == 'H' || toss == 'h') {
            cout << "You chose Head and Freya Chose Tail\n";
            game.freya_choice = 'T';
        } else {
            cout << "You chose Tail and Freya Chose Head\n";
            game.freya_choice = 'H';
        }
    } else {
        cout << "\nYou entered the wrong key, hence breaking the rule.\n";
        sleep(2);
        return 0;
    }

    while (game.player_score == game.freya_score) {
        game.player_score = 0;
        game.freya_score = 0;
        cout << "\nTossing the coin...\n";
        srand(time(0));
        game.freya_score = rand() % 5 + 1;
        sleep(2);
        srand(time(0));
        game.player_score = rand() % 5 + 1;

        cout << "You chose: " << game.player_choice << " and Freya chose: " << game.freya_choice << "\n";

        if (game.player_score > game.freya_score) {
            cout << "\tCongratulations! You won the Toss\n";
            decision('P', game);
        } else if (game.freya_score > game.player_score) {
            cout << "\tFreya won the Toss\n";
            decision('F', game);
        } else {
            cout << "\tDraw\n";
        }
    }

    return 0;
}

void decision(char alphabet, GameState &game) {
    int choice = 0;
    if (alphabet == 'P') {
        cout << "\nWhat would You like to do? Bat or Bowl?\nPress 1 for Bat\nPress 2 for Bowl\n";
        cin >> choice;
        if (choice < 1 || choice > 2) {
            cout << "You broke the rule\n";
            return;
        }
        if (choice == 1) {
            bat(game);
        } else if (choice == 2) {
            bowl(game);
        }
    }

    if (alphabet == 'F') {
        srand(time(0));
        choice = rand() % 2 + 1;
        if (choice == 1) {
            cout << "\nFreya Chose to Bat\n";
            bowl(game);
        } else {
            cout << "\nFreya Chose to Bowl\n\n";
            bat(game);
        }
    }
}

int bat(GameState &game) {
    int score_of_player = 0, score_of_freya = 0, score_player = 0;

    if (game.count == 1) {
        total(game.bat_score, game.bowl_score);
    } else if (game.count == 0) {
        game.count++;
        cout << "\n\nYou're Batting\n";
        do {
            cout << "\nEnter the Score: ";
            cin >> score_of_player;
            if (score_of_player > 6 || score_of_player < 1) {
                cout << "\nYou broke the Rule\n";
                return 0;
            }
            srand(time(0));
            score_of_freya = rand() % 6 + 1;
            if (score_of_freya != score_of_player)
                score_player += score_of_player;

            cout << "\n\n\tYou're score\tFreya score\n\t" << score_player << "\t\t" << score_of_freya << "\n";

            if (game.count1 == 1) {
                if (game.bowl_score < score_player) {
                    total(game.bat_score, score_player);
                    return 0;
                }
            }
            if (score_of_player == score_of_freya) {
                game.bat_score = score_player;
                cout << "\nYou're Out!\n";
                bowl(game);
            }
        } while (score_of_player > score_of_freya || score_of_player < score_of_freya);
    }

    return 0;
}

int bowl(GameState &game) {
    int score_of_player = 0, score_of_freya = 0, score_player = 0;

    if (game.count1 == 1) {
        total(game.bat_score, game.bowl_score);
    } else if (game.count1 == 0) {
        game.count1++;
        cout << "You're Bowling\n";
        do {
            cout << "\nEnter score: ";
            cin >> score_of_player;
            if (score_of_player > 6 || score_of_player < 1) {
                cout << "\nYou broke the rule\n";
                return 0;
            }
            srand(time(0));
            score_of_freya = rand() % 6 + 1;

            if (score_of_freya != score_of_player)
                score_player += score_of_freya;

            cout << "\nScore of Freya: " << score_of_freya;
            cout << "\n\n\n\tFreya score\tYou're bowl score\n\t" << score_player << "\t\t" << score_of_player << "\n\n\n";

            if (game.count == 1) {
                if (game.bat_score < score_player) {
                    total(game.bat_score, score_player);
                    return 0;
                }
            }
            if (score_of_player == score_of_freya) {
                game.bowl_score = score_player;
                cout << "\nFreya is Out!\n";
                bat(game);
            }
        } while (score_of_player > score_of_freya || score_of_player < score_of_freya);
    }

    return 0;
}
void total(int player, int freya) {
    cout << "\nResult is being Calculated\n";
    sleep(4);
    cout << "\nFinal Scores => You: " << player << " | Freya: " << freya << "\n";

    if (player > freya)
        cout << "\n\t\tYou won the match\n";
    else if (freya > player)
        cout << "\n\t\tFreya won the match\n";
    else
        cout << "\nMatch is drawn\n";
}
