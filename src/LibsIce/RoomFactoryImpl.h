#ifndef ROOM_FACTORY_IMPL_H
    #define ROOM_FACTORY_IMPL_H

    #include <Ice/Ice.h>
    #include "chat.h"
    #include "RoomImpl.h"
    #include "PortsUtil.h"

    using namespace std;
    using namespace Chat;

    namespace LibsIce {
        class RoomFactoryImpl : public virtual RoomFactory {
            public:
                RoomFactoryImpl();
                virtual RoomPrx createRoom(const string&, 
                                           const ::Ice::Current& = ::Ice::Current()) override;
                virtual RoomList getRooms(const ::Ice::Current& = ::Ice::Current()) override;
                ~RoomFactoryImpl();
            private:
                RoomList roomList;
                Ice::CommunicatorPtr ic;
                Ice::ObjectAdapterPtr adapter;
                PortsUtil portsUtil;
        };
    }

#endif