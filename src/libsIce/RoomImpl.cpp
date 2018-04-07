#include "RoomImpl.h"

string RoomImpl::getName(const ::Ice::Current&) {
    return roomName;
}

UserList RoomImpl::getUsers(const ::Ice::Current&) {
    return users;
}

void RoomImpl::AddUser(const UserPrx& user, const string& password, const ::Ice::Current&) {
    if (usernamesWithPasswords.find(user->getName()) != usernamesWithPasswords.end()) {
        throw new UserAlreadyExists();
    }
    users.push_back(user);
    usernamesWithPasswords.insert(usernamesWithPasswords.begin(),
                                    pair<string, string>(user->getName(), password));
}

void RoomImpl::ChangePassword(const UserPrx& user, const string& oldPassword, const string& newPassword, const ::Ice::Current&) {
    auto username = user->getName();
    auto userSavedInRoom = usernamesWithPasswords.find(username);
    if (userSavedInRoom == usernamesWithPasswords.end()) {
        throw new NoSuchUserExist();
    }
    if (userSavedInRoom->second != oldPassword) {
        throw new WrongPassword();
    }
    usernamesWithPasswords.at(username) = newPassword;
}

void RoomImpl::LeaveRoom(const UserPrx& user, const string& password, const ::Ice::Current&) {
    auto userSavedInRoom = usernamesWithPasswords.find(user->getName());
    if (userSavedInRoom == usernamesWithPasswords.end()) {
        throw new NoSuchUserExist();
    }
    if (userSavedInRoom->second != password) {
        throw new WrongPassword();
    }

    usernamesWithPasswords.erase(userSavedInRoom);
    for (auto it = users.begin(); it != users.end(); ) {
        if (*it == user) {
            it = users.erase(it);
        } else {
            ++it;
        }
    }
}

void RoomImpl::Destroy(const ::Ice::Current&) {
    usernamesWithPasswords.clear();
    users.clear();
}

void RoomImpl::SendMessage(const UserPrx& user, const string& message, const string& password, const ::Ice::Current&) {
    auto userSavedInRoom = usernamesWithPasswords.find(user->getName());
    if (userSavedInRoom == usernamesWithPasswords.end()) {
        throw new NoSuchUserExist();
    }

    if (userSavedInRoom->second != password) {
        throw new WrongPassword();
    }
    for (auto& userInRoom : users) {
     //   userInRoom->SendMessage(this, user, message);
    }
}