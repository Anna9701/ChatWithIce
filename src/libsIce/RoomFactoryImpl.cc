#include "RoomFactoryImpl.h"

RoomList RoomFactoryImpl::getRooms(const ::Ice::Current&) {
    return roomList;
}

RoomPrx createRoom(const string& name, const ::Ice::Current&) {
    Room room = new RoomImpl(name);
    roomList.push_back(&room);

    return &room;
}