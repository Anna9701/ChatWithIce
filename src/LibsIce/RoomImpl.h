#ifndef ROOM_IMPL_H
    #define ROOM_IMPL_H

    #include "chat.h"
    #include <Ice/Ice.h>
    #include "PortsUtil.h"
    #include "RoomFactoryImpl.h"

    using namespace std;
    using namespace Chat;

    namespace LibsIce {
        class RoomImpl : public virtual Room {
            public:
                RoomImpl(const string &n) : roomName(n) {}
                virtual string getName(const ::Ice::Current& = ::Ice::Current()) override;
                virtual UserList getUsers(const ::Ice::Current& = ::Ice::Current()) override;
                virtual void AddUser(const UserPrx&, 
                                     const string&, 
                                     const ::Ice::Current& = ::Ice::Current()) override;
                virtual void ChangePassword(const UserPrx&, 
                                            const string&, 
                                            const string&, 
                                            const ::Ice::Current& = ::Ice::Current()) override;
                virtual void SendMessage(const UserPrx&, 
                                         const string&, 
                                         const string&, 
                                         const ::Ice::Current& = ::Ice::Current()) override;
                virtual void Destroy(const ::Ice::Current& = ::Ice::Current()) override;
                virtual void LeaveRoom(const UserPrx&, 
                                       const string&, 
                                       const ::Ice::Current& = ::Ice::Current()) override;
            private:
                string roomName;
                UserList users;
                UsernamesWithPasswordList usernamesWithPasswords; 
        };
    }

#endif
