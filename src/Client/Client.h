#ifndef CLIENT_H
    #define CLIENT_H

    #include <thread>
    #include <Ice/Ice.h>
    #include "chat.h"
    #include "UserImpl.h"
    #include "PortsUtil.h"
    
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
                void joinToRoom();
                void printUsersInRoom() const;
                void leaveRoom();
                ~Client();
            private:
                string username;
                string password;
                UserPrx user;
                ServerPrx server;
                Ice::CommunicatorPtr iceCommunicator;
                Ice::ObjectAdapterPtr adapter;
                PortsUtil portsUtil;
                RoomList userRooms;

                void createUser();
                string getNameOfTheRoom() const;
                void clearConsole() const;
        }; 
    }

#endif