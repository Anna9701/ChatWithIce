#include "Client.h"
#include "ServerImpl.h"
#include "Menu.h"

using namespace std;
using namespace ClientApp;

int main(int argc, char* argv[]) {
    int status = 0;
    Menu menu;
    string username, password;

    cout << "Enter your username: " << endl;
    cin >> username;
    cout << "Enter your password: " << endl;
    cin >> password;

    Client client(username, password);

    while (true) {
        menu.printMenu();
        int choice = menu.getChoice();
        switch (choice) {
            case 1:
                client.createRoom();
                break;
            case 2:
                client.printListAllRooms();
                break;
            case 0:
                return status;
        }
    }

    return status;
}