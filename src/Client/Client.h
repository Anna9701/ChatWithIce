#ifndef CLIENT_H
    #define CLIENT_H

    #define MAX_PORT_NUMBER 51000
    #define MIN_PORT_NUMBER 10001

    #include <thread>
    #include <Ice/Ice.h>
    #include "chat.h"
    #include "UserImpl.h"
    #include <random>
    
    using namespace std;
    using namespace Chat;
    using namespace LibsIce;

    namespace ClientApp {
        class Client {
            public:
                Client(const string&, const string&);
                void setPassword(const string&);
                void createRoom() const;
                void printListAllRooms() const;
                ~Client();
            private:
                string username;
                string password;
                UserPrx user;
                ServerPrx server;
                Ice::CommunicatorPtr iceCommunicator;
                Ice::ObjectAdapterPtr adapter;

                void createUser();
                int getRandomPort() const;
        }; 
    }

#endif