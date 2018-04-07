#include "Menu.h"

namespace ClientApp {
    void Menu::printMenu() {
        cout << "Hello. What do you want to do?" << endl;
        cout << "1. Create room" << endl;
        cout << "2. Find room" << endl;
        cout << "3. Get all available rooms" << endl;
        cout << "4. Join to room" << endl;
        cout << "5. Leave room" << endl;
        cout << "6. Send message to room" << endl;
        cout << "7. Get list of users in room" << endl;
        cout << "8. Send private message to other user" << endl;
        //cout << "9. Register as room factory" << endl;
        cout << "0. Exit" << endl;
    }

    void Menu::getInput() {
        cin >> choice; 
        while (choice < 0 || choice > 8) {
            cout << "Unkown option, please, enter valid number" << endl;
            cin >> choice;
        }
    }

    int Menu::getChoice() {
        getInput();
        return choice;
    }
}