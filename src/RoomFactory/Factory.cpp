#include "Factory.h"

namespace RoomFactory {
    void Factory::registerRoomFactory() {
        RoomFactoryPtr object = new RoomFactoryImpl();
        int port = getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("RoomFactory", 
                                                                    "default -p " + to_string(port));
        adapter->add(object, iceCommunicator->stringToIdentity("RoomFactory"));
        adapter->activate();
        Ice::ObjectPrx base = iceCommunicator->stringToProxy("RoomFactory:default -p " + to_string(port));
        roomFactory = RoomFactoryPrx::checkedCast(base);
        server->RegisterRoomFactory(roomFactory);
        iceCommunicator->waitForShutdown();
    }

    void Factory::unregisterRoomFactory() const {
        server->UnregisterRoomFactory(roomFactory);
    }

    int Factory::getRandomPort() const {
        random_device rseed;
        mt19937 randomGenerator(rseed());
        uniform_int_distribution<> distribution(MIN_PORT_NUMBER, MAX_PORT_NUMBER);

        return distribution(randomGenerator);
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
}