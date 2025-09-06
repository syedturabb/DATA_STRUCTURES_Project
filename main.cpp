#include <iostream>
using namespace std;
void StartG1();
void StartG2();
void StartG3();

int main() {
    int choice;

    do {
        cout << "\n\n\n";
        cout << "\t\t\t=== 🎮 GameBox Menu ===\n";
        cout << "\n";
        cout << "\t\t\t1. Mine Sweeper Game\n";
        cout << "\n";
        cout << "\t\t\t2. Snake & Ladder Game\n";
        cout << "\n";
        cout << "\t\t\t3. Heads & Tails Game\n";
        cout << "\n";
        cout << "\t\t\t0. Exit\n";
        cout << "\n";
        cout << "\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                StartG1();
                break;
            case 2:
                StartG2();
                break;
            case 3:
                StartG3();
                break;
            case 0:
                cout << "Thanks for playing!\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }

    } while (choice != 0);

    return 0;
}
