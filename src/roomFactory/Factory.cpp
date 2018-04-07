#include "Factory.h"

void Factory::registerRoomFactory() {
    RoomFactoryPtr object = new RoomFactoryImpl();
    adapter = iceCommunicator->createObjectAdapterWithEndpoints("RoomFactory", "default -p 10001");
    adapter->add(object, iceCommunicator->stringToIdentity("RoomFactory"));
    adapter->activate();
    Ice::ObjectPrx base = iceCommunicator->stringToProxy("RoomFactory:default -p 10001");
    roomFactory = RoomFactoryPrx::checkedCast(base);
    server->RegisterRoomFactory(roomFactory);
    iceCommunicator->waitForShutdown();
}

void Factory::unregisterRoomFactory() const {
    server->UnregisterRoomFactory(roomFactory);
}

Factory::Factory() {
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
}

Factory::~Factory() {
    unregisterRoomFactory();
}