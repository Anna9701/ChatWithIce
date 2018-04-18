#include "RoomImpl.h"

namespace LibsIce {
    string RoomImpl::getName(const ::Ice::Current&) {
        return roomName;
    }

    UserList RoomImpl::getUsers(const ::Ice::Current&) {
        return users;
    }

    void RoomImpl::AddUser(const UserPrx& user, const string& password, const ::Ice::Current&) {
        if (usernamesWithPasswords.find(user->getName()) != usernamesWithPasswords.end()) {
            throw UserAlreadyExists();
        }
        users.push_back(user);
        usernamesWithPasswords.insert(usernamesWithPasswords.begin(),
                                        pair<string, string>(user->getName(), password));
    }

    void RoomImpl::ChangePassword(const UserPrx& user, 
                                  const string& oldPassword, 
                                  const string& newPassword, 
                                  const ::Ice::Current&) {
        auto username = user->getName();
        auto userSavedInRoom = usernamesWithPasswords.find(username);
        if (userSavedInRoom == usernamesWithPasswords.end()) {
            throw NoSuchUserExist();
        }
        if (userSavedInRoom->second != oldPassword) {
            throw WrongPassword();
        }
        usernamesWithPasswords.at(username) = newPassword;
    }

    void RoomImpl::LeaveRoom(const UserPrx& user, const string& password, const ::Ice::Current&) {
        auto userSavedInRoom = usernamesWithPasswords.find(user->getName());
        if (userSavedInRoom == usernamesWithPasswords.end()) {
            throw NoSuchUserExist();
        }
        if (userSavedInRoom->second != password) {
            throw WrongPassword();
        }
        usernamesWithPasswords.erase(userSavedInRoom);
        for (auto usersIterator = users.begin(); usersIterator != users.end(); ++usersIterator) {
            if ((*usersIterator) == user) {
                usersIterator = users.erase(usersIterator);
                break;
            } 
        }
        cout << "Removed user " << user->getName() << " from room" << endl;
    }

    void RoomImpl::Destroy(const ::Ice::Current&) {
        usernamesWithPasswords.clear();
        users.clear();
    }

    void RoomImpl::SendMessage(const UserPrx& user, 
                               const string& message, 
                               const string& password, 
                               const ::Ice::Current&) {
        auto userSavedInRoom = usernamesWithPasswords.find(user->getName());
        if (userSavedInRoom == usernamesWithPasswords.end()) {
            throw NoSuchUserExist();
        }

        if (userSavedInRoom->second != password) {
            throw WrongPassword();
        }

        for (auto& userInRoom : users) {
            userInRoom->SendMessage(roomName, user, message);
        }
    }
}