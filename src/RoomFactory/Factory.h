#ifndef FACTORY_H
    #define FACTORY_H

    #include <Ice/Ice.h>
    #include "chat.h"
    #include "RoomFactoryImpl.h"
    #include "PortsUtil.h"

    using namespace std;
    using namespace Chat;
    using namespace LibsIce;

    namespace RoomFactory {
        class Factory {
            public:
                Factory();
                void registerRoomFactory();
                ~Factory();
            private:
                ServerPrx server;
                Ice::CommunicatorPtr iceCommunicator;
                Ice::ObjectAdapterPtr adapter;
                RoomFactoryPrx roomFactory;
                PortsUtil portsUtil;
        };
    }

#endif