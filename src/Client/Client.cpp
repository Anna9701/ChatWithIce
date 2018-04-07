#include "Client.h"

namespace ClientApp {
    void Client::setPassword(const string& password) {
        this->password = password;
    }

    void Client::createUser() {
        UserPtr object = new UserImpl(username);
        int port = getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("User" + username, "default -p " + to_string(port));
        adapter->add(object, iceCommunicator->stringToIdentity("User" + username));
        adapter->activate();
        Ice::ObjectPrx base = iceCommunicator->stringToProxy("User" + username + ":default -p " + to_string(port));
        user = UserPrx::checkedCast(base);
    }

    Client::Client(const string& name, const string& passwd) : username(name), password(passwd) {
        try {
            iceCommunicator = Ice::initialize();
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p 10000");
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

    int Client::getRandomPort() const {
        random_device rseed;
        mt19937 randomGenerator(rseed());
        uniform_int_distribution<> distribution(MIN_PORT_NUMBER, MAX_PORT_NUMBER);

        return distribution(randomGenerator);
    }
}