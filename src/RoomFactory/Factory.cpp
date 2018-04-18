#include "Factory.h"

namespace RoomFactory {
    void Factory::registerRoomFactory() {
        RoomFactoryPtr object = new RoomFactoryImpl();
        int port = portsUtil.getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("RoomFactory", "default -p " + to_string(port));
        roomFactory = RoomFactoryPrx::uncheckedCast(adapter->addWithUUID(object));
        adapter->add(object, iceCommunicator->stringToIdentity("RoomFactory"));
        adapter->activate();
        server->RegisterRoomFactory(roomFactory);
        iceCommunicator->waitForShutdown();
    }

    Factory::Factory() {
        try {
            iceCommunicator = Ice::initialize();
            int serverPort = portsUtil.getServerPort();
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p " + to_string(serverPort));
            server = ServerPrx::checkedCast(base);
            if (!server) {
                throw "Invalid proxy";
            }
        } catch (const RoomAlreadyExist &ex) {
            cerr << ex << endl;
        } catch (const NoSuchRoomExist& ex) {
            cerr << ex << endl;
        } catch (const UserAlreadyExists& ex) {
            cerr << "Such userr already exist" << endl;
        } catch (const Ice::Exception& ex) {
            cerr << ex << endl;
        } catch (const char* msg) {
            cerr << msg << endl;
        }
    }

    Factory::~Factory() {
        server->UnregisterRoomFactory(roomFactory);
    }
}