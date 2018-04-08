#include "UserImpl.h"
namespace LibsIce {
    string UserImpl::getName(const Ice::Current&) { 
        return name;
    }

    void UserImpl::SendMessage(const string& room, 
                            const UserPrx& who, 
                            const string& message, 
                            const ::Ice::Current&) {
        auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << ctime(&currentTime) << room << "->" << who->getName() << ":" << message << endl;
    }

    void UserImpl::SendPrivateMessage(const UserPrx& who, 
                                    const string& message, 
                                    const ::Ice::Current&) {
        auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << ctime(&currentTime) << who->getName() << ": " << message << endl;
    }
}