#include "RoomFactoryImpl.h"

namespace LibsIce {
    RoomList RoomFactoryImpl::getRooms(const ::Ice::Current&) {
        return roomList;
    }

    RoomPrx RoomFactoryImpl::createRoom(const string& name, const ::Ice::Current&) {
        RoomPtr object = new RoomImpl(name);
        cout << "RoomFactory::Creating room " << name << endl;
        adapter = ic->createObjectAdapterWithEndpoints("SimpleRoom" + name, "default -p 10003");
        adapter->add(object, ic->stringToIdentity("SimpleRoom" + name));
        Ice::ObjectPrx base = ic->stringToProxy("SimpleRoom" + name + ":default -p 10003");
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