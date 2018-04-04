#ifndef USER_I
    #define USER_I

    #include <Ice/Ice.h>
    #include "chat.h"

    using namespace Chat;
    using namespace std;

    class UserI : public User {
        public:
            UserI(string n) : name(n){};
            virtual string getName(const Ice::Current&);
            virtual void SendMessage(const RoomPrx&, const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) {} //TODO
            virtual void SendPrivateMessage(const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) {}
        private:
            string name;
    };
    
#endif