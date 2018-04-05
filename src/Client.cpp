#include "Client.h"

void Client::setUsername(const string& name) {
    username = name;
}

void Client::setPassword(const string& password) {
    this->password = password;
}

void Client::sendUser() const {
    server->RegisterUser(username, password);
}

Client::Client(int argc, char* argv[]) {
     try {
        iceCommunicator = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = iceCommunicator->stringToProxy("SimpleServer:default -p 10000");
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