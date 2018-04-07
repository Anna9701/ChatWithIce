#include "Client.h"

namespace ClientApp {
    void Client::setUsername(const string& name) {
        username = name;
    }

    void Client::setPassword(const string& password) {
        this->password = password;
    }

    void Client::createUser() {
        UserPtr object = new UserImpl(username);
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("User" + username, "default -p 10000");
        adapter->add(object, iceCommunicator->stringToIdentity("User" + username));
        adapter->activate();
        Ice::ObjectPrx base = iceCommunicator->stringToProxy("User" + username + ":default -p 10000");
        user = UserPrx::checkedCast(base);
    }

    Client::Client(int argc, char* argv[]) {
        try {
            iceCommunicator = Ice::initialize(argc, argv);
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p 10000");
            server = ServerPrx::checkedCast(base);
            if (!server)
                throw "Invalid proxy";
        } catch (const Ice::Exception& ex) {
            cerr << ex << endl;
        } catch (const char* msg) {
            cerr << msg << endl;
        }
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
}