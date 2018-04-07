#include "Client.h"
#include "ServerImpl.h"
#include "Menu.h"

using namespace std;
using namespace ClientApp;

int main(int argc, char* argv[]) {
    int status = 0;
    Menu menu;
    Client client(argc, argv);
    string clientInput;

    cout << "Enter your username: " << endl;
    cin >> clientInput;
    client.setUsername(clientInput);
    cout << "Enter your password: " << endl;
    cin >> clientInput;
    client.setPassword(clientInput);

    while (true) {
        menu.printMenu();
        int choice = menu.getChoice();
        switch (choice) {
            case 1:
                client.createRoom();
                break;
            case 0:
                return status;
        }
    }

    return status;
}