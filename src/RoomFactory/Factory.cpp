#include "Factory.h"

namespace RoomFactory {
    void Factory::registerRoomFactory() {
        RoomFactoryPtr object = new RoomFactoryImpl();
        int port = portsUtil.getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("RoomFactory", 
                                                        "default -p " + to_string(port));
        adapter->add(object, iceCommunicator->stringToIdentity("RoomFactory"));
        adapter->activate();
        Ice::ObjectPrx base = iceCommunicator->stringToProxy("RoomFactory:default -p " 
                                                                    + to_string(port));
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
            int serverPort = portsUtil.getServerPort();
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p " 
                                                            + to_string(serverPort));
            server = ServerPrx::checkedCast(base);
            if (!server) {
                throw "Invalid proxy";
            }
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