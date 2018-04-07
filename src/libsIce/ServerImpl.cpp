#include "ServerImpl.h"

RoomPrx ServerImpl::CreateRoom(const string& name, const ::Ice::Current&) {
    for (auto &room : roomList) {
        if (room->getName() == name) {
            throw new RoomAlreadyExist();
        }
    }
    //TODO random select room factory
    if (roomFactoryList.empty()) {
        throw NoResourcesAvailable();
    }
    RoomFactoryPrx roomFactory = roomFactoryList.back();
    RoomPrx room = roomFactory->createRoom(name);
    cout << "Creating room with name: " << name << endl;
    roomList.push_back(room);
    cout << "Room " << name << " created." << endl;
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
    cout << "Room factory registred " << endl;
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