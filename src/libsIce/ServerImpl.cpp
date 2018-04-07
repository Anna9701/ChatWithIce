#include "ServerImpl.h"

RoomPrx ServerImpl::CreateRoom(const string& name, const ::Ice::Current&) {
    for (auto &room : roomList) {
        if (room->getName() == name) {
            throw new RoomAlreadyExist();
        }
    }
    //TODO random select room factory
    RoomFactoryPrx roomFactory = roomFactoryList.back();
    RoomPrx room = roomFactory->createRoom(name);
    roomList.push_back(room);
    return room;
}

RoomList ServerImpl::getRooms(const ::Ice::Current&) {
    return roomList;
}

RoomPrx ServerImpl::FindRoom(const string& name, const ::Ice::Current& ) {
    for (auto &room : roomList) {
        if (room->getName() == name) {
            return room;
        }
    }
    throw new NoSuchRoomExist();   
}

void ServerImpl::RegisterRoomFactory(const RoomFactoryPrx& roomFactory, const ::Ice::Current&) {
    roomFactoryList.push_back(roomFactory);
}

void ServerImpl::UnregisterRoomFactory(const RoomFactoryPrx& roomFactory, const ::Ice::Current&) {
    for (auto registredFactoryIt = roomFactoryList.begin(); registredFactoryIt != roomFactoryList.end(); ) {
        if (*registredFactoryIt == roomFactory) {
            registredFactoryIt = roomFactoryList.erase(registredFactoryIt);
        } else {
            ++registredFactoryIt;
        }
    }
}