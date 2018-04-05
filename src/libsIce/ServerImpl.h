#ifndef SERVER_IMPL_H
    #define SERVER_IMPL_H

    #include <Ice/Ice.h>
    #include "chat.h"

    using namespace Chat;
    using namespace std;

    class ServerImpl : public Server {
        public:
            virtual RoomPrx CreateRoom(const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual RoomList getRooms(const ::Ice::Current& = ::Ice::Current()) override;
            virtual RoomPrx FindRoom(const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual void RegisterUser(const string&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual void ChangePassword(const UserPrx&, const string&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual void getPassword(const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual void RegisterRoomFactory(const RoomFactoryPrx&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual void UnregisterRoomFactory(const RoomFactoryPrx&, const ::Ice::Current& = ::Ice::Current()) override;
        private:
    };

#endif