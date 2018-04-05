#include "ServerImpl.h"

void ServerImpl::RegisterUser(const string& username, const string& password, const ::Ice::Current&) {
    UserPtr user = new UserImpl(username);
    //usersList.push_back(user);
    cout << password << endl << user->getName() << endl;
}
/*******************************NOT IMPLEMENTED YET**********************************************************************/
RoomPrx ServerImpl::CreateRoom(const string& name, const ::Ice::Current&) {
    cout << name;
    return NULL;
}

RoomList ServerImpl::getRooms(const ::Ice::Current&) {
    RoomList roomList;
    return roomList;
}

RoomPrx ServerImpl::FindRoom(const string& name, const ::Ice::Current& ) {
    cout << name;
    return NULL;   
}

void ServerImpl::ChangePassword(const UserPrx& user, const string& oldPassword, const string& newPassword, const ::Ice::Current&) {
    cout << oldPassword << newPassword << user;
}

void ServerImpl::getPassword(const string& username, const ::Ice::Current&) {
    cout << username;
}

void ServerImpl::RegisterRoomFactory(const RoomFactoryPrx& roomFactory, const ::Ice::Current&) {
    cout << roomFactory;
}

void ServerImpl::UnregisterRoomFactory(const RoomFactoryPrx& roomFactory, const ::Ice::Current&) {
    cout << roomFactory;
}