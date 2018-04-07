#include "UserImpl.h"
namespace LibsIce {
    string UserImpl::getName(const Ice::Current&) { 
        return name;
    }

    void UserImpl::SendMessage(const RoomPrx& room, 
                            const UserPrx& who, 
                            const string& message, 
                            const ::Ice::Current&) {
        cout << room->getName() << " : " << who->getName() << " wrote: " << message << endl;
    }

    void UserImpl::SendPrivateMessage(const UserPrx& who, 
                                    const string& message, 
                                    const ::Ice::Current&) {
        cout << who->getName() << " wrote: " << message << endl;
    }
}