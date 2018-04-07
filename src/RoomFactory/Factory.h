#ifndef FACTORY_H
    #define FACTORY_H

    #define MAX_PORT_NUMBER 51000
    #define MIN_PORT_NUMBER 10001

    #include <Ice/Ice.h>
    #include "chat.h"
    #include "RoomFactoryImpl.h"
    #include <random>
    #include <cstdlib>

    using namespace std;
    using namespace Chat;
    using namespace LibsIce;

    namespace RoomFactory {
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

                int getRandomPort() const;
        };
    }

#endif