#include "RoomFactoryImpl.h"

namespace LibsIce {
    RoomList RoomFactoryImpl::getRooms(const ::Ice::Current&) {
        return roomList;
    }

    RoomPrx RoomFactoryImpl::createRoom(const string& name, const ::Ice::Current&) {
        RoomPtr object = new RoomImpl(name);
        cout << "RoomFactory::Creating room " << name << endl;
        int port = portsUtil.getRandomPort();

        adapter = ic->createObjectAdapterWithEndpoints("SimpleRoom" + name, "default -p " + to_string(port));
        adapter->add(object, ic->stringToIdentity("SimpleRoom" + name));
        adapter->activate();
        Ice::ObjectPrx base = ic->stringToProxy("SimpleRoom" + name + ":default -p " + to_string(port));
        RoomPrx room = RoomPrx::checkedCast(base);
        roomList.push_back(room);
        cout << "RoomFactory::Room created" << endl;
        return room;
    }

    RoomFactoryImpl::RoomFactoryImpl() {
        ic = Ice::initialize();
    }

    RoomFactoryImpl::~RoomFactoryImpl() {
        if (ic) {
            try {
                ic->destroy();
            } catch (const Ice::Exception& e) {
                cerr << e << endl;
            }
        }
    }
}