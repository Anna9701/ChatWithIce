#include "Client.h"

namespace ClientApp {
    void Client::setPassword(const string& password) {
        this->password = password;
    }

    void Client::createUser() {
        UserPtr object = new UserImpl(username);
        int port = portsUtil.getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("User" + username, 
                                                        "default -p " + to_string(port));
        adapter->add(object, iceCommunicator->stringToIdentity("User" + username));
        adapter->activate();
        Ice::ObjectPrx base = iceCommunicator->stringToProxy("User" + username 
                                                + ":default -p " + to_string(port));
        user = UserPrx::checkedCast(base);
    }

    Client::Client(const string& name, const string& passwd) : username(name), password(passwd) {
        try {
            iceCommunicator = Ice::initialize();
            int serverPort = portsUtil.getServerPort();
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p " 
                                                            + to_string(serverPort));
            server = ServerPrx::checkedCast(base);
            if (!server)
                throw "Invalid proxy";
        } catch (const Ice::Exception& ex) {
            cerr << ex << endl;
        } catch (const char* msg) {
            cerr << msg << endl;
        }
        createUser();
    }

    Client::~Client() {
        if (iceCommunicator)
            iceCommunicator->destroy();
    }

    void Client::createRoom() const {
        clearConsole();
        string roomName;
        cout << "Enter name for new room " << endl;
        cin >> roomName;
        server->CreateRoom(roomName);
        clearConsole();
    }

    void Client::printListAllRooms() const {
        clearConsole();
        auto rooms = server->getRooms();
        cout << "Available rooms are: " << endl;
        for (auto room : rooms) {
            cout << room->getName() << endl;
        }
        cout << endl;
    }

    void Client::joinToRoom() {
        string name = getNameOfTheRoom();
        try {
            RoomPrx room = server->FindRoom(name);
            room->AddUser(user, password);
            userRooms.push_back(room);
        } catch (NoSuchRoomExist& ex) {
            cerr << ex << endl;
        } catch (UserAlreadyExists& ex) {
            cerr << ex << endl;
        }
        clearConsole();
    }

    void Client::printUsersInRoom() const {
        clearConsole();
        string roomName = getNameOfTheRoom();
        cout << "Users available in room " << roomName << endl;
        try {
            RoomPrx room = server->FindRoom(roomName);
            auto users = room->getUsers();
            for (auto& user : users) {
                cout << user->getName() << endl;
            }
        } catch (NoSuchRoomExist& ex) {
            cerr << ex << endl;
        }
    }

    string Client::getNameOfTheRoom() const {
        clearConsole();
        string roomName;
        cout << "Enter the name of the room:" << endl;
        cin >> roomName;
        return roomName;
    }

    void Client::leaveRoom() {
        clearConsole();
        string roomName = getNameOfTheRoom();
        for (auto roomsIterator =  userRooms.begin(); roomsIterator != userRooms.end(); ++roomsIterator) {
            if ((*roomsIterator)->getName() == roomName) {
                try {
                    (*roomsIterator)->LeaveRoom(user, password);
                    cout << "Leaving room " << roomName << endl;
                    userRooms.erase(roomsIterator);
                    return;
                } catch (NoSuchUserExist& ex) {
                    cerr << "Ooopss.. something is wrong. You couldn't be found on user list for that room. Sorry!" << endl;
                } catch (WrongPassword& ex) {
                    cerr << "Provided password was incorrect. Can't remove user from room" << endl;
                }
            }
        }
        cerr << "You were not joined to room " << roomName << endl;
    }

    void Client::clearConsole() const {
        for (unsigned int i = 0; i < 100; ++i) {
            cout << endl;
        }
    }

    void Client::changePassword() {
        clearConsole();
        string newPassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        for (auto& room : userRooms) {
            try {
                room->ChangePassword(user, password, newPassword);
            } catch (NoSuchUserExist& ex) {
                cerr << "No such user in room " << room->getName() << ". Something went wrong, we are sorry!" << endl;
            } catch (WrongPassword& ex) {
                cerr << "Provided password was incorrect. Cannot change." << endl;
            }
        }
        password = newPassword;
    }
}