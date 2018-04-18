#include "Client.h"

namespace ClientApp {
    void Client::setPassword(const string& password) {
        this->password = password;
    }

    void Client::createUser() {
        UserPtr object = new UserImpl(username);
        int port = portsUtil.getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("User" + username, "default -p " + to_string(port));
        user = UserPrx::uncheckedCast(adapter->addWithUUID(object));
        adapter->activate();
    }

    Client::Client(const string& name, const string& passwd) : username(name), password(passwd) {
        try {
            iceCommunicator = Ice::initialize();
            int serverPort = portsUtil.getServerPort();
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p " + to_string(serverPort));
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
        for (auto &room : userRooms) {
            room->LeaveRoom(user, password);
        }
        if (iceCommunicator)
            iceCommunicator->destroy();
    }

    void Client::createRoom() const {
        scrollConsole();
        string roomName;
        cout << "Enter name for new room " << endl;
        cin >> roomName;
        cin.ignore(1000, '\n');
        try {
            server->CreateRoom(roomName);
        } catch (const Chat::RoomAlreadyExist& ex) {
            cerr << "Cannot create. There is a room with that name already." << endl;
        } catch (const Chat::NoResourcesAvailable& ex) {
            cerr << "Cannot create. There is no resources available. Try again later." << endl;
        } catch (const Ice::UnknownException& ex) {
            cerr << "Cannot create" << endl;
        }
        scrollConsole();
    }

    void Client::printListAllRooms() const {
        scrollConsole();
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
        } catch (const NoSuchRoomExist& ex) {
            cerr << "There is no such room" << endl;
        } catch (const UserAlreadyExists& ex) {
            cerr << "Such userr already exist" << endl;
        } catch (const Ice::UnknownException& ex) {
            cerr << "Operation couldn't be realized." << endl;
        }
        scrollConsole();
    }

    void Client::printUsersInRoom() const {
        try {
            auto users = getUsersInRoom();
            scrollConsole();
            cout << "Users available in room " << endl;
            for (auto& user : users) {
                cout << user->getName() << endl;
            }
        } catch (const Ice::UnknownException& ex) {
            cerr << "Operation couldn't be realized." << endl;
        }
    }

    UserList Client::getUsersInRoom() const {
        string roomName = getNameOfTheRoom();
        try {
            RoomPrx room = server->FindRoom(roomName);
            UserList users = room->getUsers();
            return users;
        } catch (const NoSuchRoomExist& ex) {
            cerr << "There is no such room" << endl;
        } catch (Ice::UnknownException& ex) {
            cerr << ex << endl;
        }
        return UserList();
    }

    string Client::getNameOfTheRoom() const {
        scrollConsole();
        string roomName;
        cout << "Enter the name of the room:" << endl;
        cin >> roomName;
        cin.ignore(1000, '\n');
        return roomName;
    }

    void Client::leaveRoom() {
        scrollConsole();
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
                } catch (Ice::UnknownException& ex) {
                    cerr << ex << endl;
                }
            }
        }
        cerr << "You were not joined to room " << roomName << endl;
    }

    void Client::scrollConsole() const {
        for (unsigned int i = 0; i < 2; ++i) {
            cout << endl;
        }
    }

    void Client::changePassword() {
        scrollConsole();
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

    void Client::sendPrivateMessageToUser() const {
        string targetUsername;
        UserList usersAvailable;
        try {
            usersAvailable = getUsersInRoom();
        } catch (NoSuchRoomExist& ex) {
            cerr << ex << endl;
            return;
        }
        cout << "Enter the name of the user you want to write to" << endl;
        cin >> targetUsername;
        cin.ignore(1000, '\n');
        for(auto& targetUser : usersAvailable) {
            if (targetUser->getName() == targetUsername) {
                string message;
                cout << "Enter the content of message you want to send to" << endl;
                getline(cin, message);
                targetUser->SendPrivateMessage(user, message);
                return;
            }
        }
        cerr << "No such user found. Sorry." << endl;
    }

    void Client::sendMessageToRoom() const {
        scrollConsole();
        string targetRoom = getNameOfTheRoom();
        for (auto roomsIterator =  userRooms.begin(); roomsIterator != userRooms.end(); ++roomsIterator) {
            if ((*roomsIterator)->getName() == targetRoom) {
                try {
                    string content;
                    cout << "Please, enter content of message you want to send to" << endl;
                    getline(cin, content);
                    (*roomsIterator)->SendMessage(user, content, password);
                    return;
                } catch (NoSuchUserExist& ex) {
                    cerr << "Ooopss.. something is wrong. You couldn't be found on user list for that room. Sorry!" << endl;
                    return;
                } catch (WrongPassword& ex) {
                    cerr << "Provided password was incorrect. Can't send message to that room" << endl;
                    return;
                }
            }
        }
        cerr << "You are not joined to room " << targetRoom << endl;
    }
}