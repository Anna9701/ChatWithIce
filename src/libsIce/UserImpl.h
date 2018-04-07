#ifndef USER_IMPL_H
    #define USER_IMPL_H

    #include <Ice/Ice.h>
    #include "chat.h"

    using namespace Chat;
    using namespace std;

    class UserImpl : public User {
        public:
            UserImpl(const string& n) : name(n){};
            virtual string getName(const Ice::Current&) override;
            virtual void SendMessage(const RoomPrx&, const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual void SendPrivateMessage(const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
        private:
            string name;
    };
    
#endif