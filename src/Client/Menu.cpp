#include "Menu.h"

namespace ClientApp {
    void Menu::printMenu() {
        cout << endl;
        cout << "Hello. What do you want to do?" << endl;
        cout << "1. Create room" << endl;
        cout << "2. Get all available rooms" << endl;
        cout << "3. Join to room" << endl;
        cout << "4. Leave room" << endl;
        cout << "5. Send message to room" << endl;
        cout << "6. Get list of users in room" << endl;
        cout << "7. Send private message to other user" << endl;
        cout << "0. Exit" << endl;
        cout << endl;
    }

    void Menu::getInput() {
        cin >> choice; 
        while (choice < 0 || choice > 7) {
            cout << "Unkown option, please, enter valid number" << endl;
            cin >> choice;
        }
    }

    int Menu::getChoice() {
        getInput();
        return choice;
    }
}