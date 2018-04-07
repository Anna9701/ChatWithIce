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
        string roomName;
        cout << "Enter name for new room " << endl;
        cin >> roomName;
        server->CreateRoom(roomName);
    }

    void Client::printListAllRooms() const {

    }
}