#include "RoomImpl.h"

string RoomImpl::getName(const ::Ice::Current&) {
    return roomName;
}

UserList RoomImpl::getUsers(const ::Ice::Current&) {
    return users;
}

void RoomImpl::AddUser(const UserPrx& user, const string& password, const ::Ice::Current&) {
    if (usersWithPasswords.find(user) != usersWithPasswords::end()) {
        throw new UserAlreadyExists();
    }
    usersList.push_back(user);
    usersWithPasswords.insert(user, password);
}

void RoomImpl::ChangePassword(const UserPrx& user, const string& oldPassword, const string& newPassword, const ::Ice::Current&) {
    auto userSavedInRoom = usersWithPasswords.find(user);
    if (userSavedInRoom == usersWithPasswords::end()) {
        throw new NoSuchUserExist();
    }
    auto oldPasswordSavedInRoom = userSavedInRoom.second;
    if (oldPasswordSavedInRoom != oldPassword) {
        throw new WrongPassword();
    }
    usersWithPasswords.at(user) = newPassword;
}

void RoomImpl::LeaveRoom(const UserPrx& user, const string& password, const ::Ice::Current&) {
    auto userSavedInRoom = usersWithPasswords.find(user);
    if (userSavedInRoom == usersWithPasswords::end()) {
        throw new NoSuchUserExist();
    }
    auto savedPassword = userSavedInRoom.second;
    if (savedPassword != password) {
        throw new WrongPassword();
    }
    usersWithPasswords.erase(userSavedInRoom);

    for (auto it = users.begin(); it != users.end(); ) {
        if (*it == user) {
            it = c.erase(it);
        } else {
            ++it;
        }
    }
}

void RoomImpl::Destroy(const ::Ice::Current&) {
    usersWithPassword.clear();
    users.clear();
}

void RoomImpl::SendMessage(const UserPrx& user, const string& message, const string& password, const ::Ice::Current&) {
    auto userSavedInRoom = usersWithPasswords.find(user);
    if (userSavedInRoom == usersWithPasswords::end()) {
        throw new NoSuchUserExist();
    }
    auto savedPassword = userSavedInRoom.second;
    if (savedPassword != password) {
        throw new WrongPassword();
    }
    for (auto& userInRoom : users) {
        userInRoom->SendMessage(this, user, message)
    }
}