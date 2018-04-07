#ifndef FACTORY_H
    #define FACTORY_H

    #include <Ice/Ice.h>
    #include "chat.h"
    #include "RoomFactoryImpl.h"

    using namespace std;
    using namespace Chat;

    class Factory {
        public:
            Factory();
            void unregisterRoomFactory() const;
            void registerRoomFactory();
            ~Factory();
        private:
            ServerPrx server;
            Ice::CommunicatorPtr iceCommunicator;
            Ice::ObjectAdapterPtr adapter;
            RoomFactoryPrx roomFactory;
    };

#endif