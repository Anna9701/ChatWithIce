#include "RoomFactoryImpl.h"

RoomList RoomFactoryImpl::getRooms(const ::Ice::Current&) {
    return roomList;
}

RoomPrx RoomFactoryImpl::createRoom(const string& name, const ::Ice::Current&) {
    RoomPtr object = new RoomImpl(name);
    adapter = ic->createObjectAdapterWithEndpoints("SimpleRoom" + name, "default -p 10000");
    adapter->add(object, ic->stringToIdentity("SimpleRoom" + name));
    Ice::ObjectPrx base = ic->stringToProxy("SimpleRoom" + name + ":default -p 10000");
    RoomPrx room = RoomPrx::checkedCast(base);
    roomList.push_back(room);

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