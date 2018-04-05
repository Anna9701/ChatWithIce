#ifndef ROOM_FACTORY_IMPL_H
    #define ROOM_FACTORY_IMPL_H

    #include <Ice/Ice.h>
    #include "chat.h"

    using namespace std;
    using namespace Chat;

    class RoomFactoryImpl : public RoomFactory {
        public:
            virtual RoomPrx createRoom(const string&, const ::Ice::Current& = ::Ice::Current()) override;
            virtual RoomList getRooms(const ::Ice::Current& = ::Ice::Current()) override;
        private:
    };

#endif