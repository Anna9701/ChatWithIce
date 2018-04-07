#ifndef CLIENT_H
    #define CLIENT_H

    #include <thread>
    #include <Ice/Ice.h>
    #include "chat.h"
    #include "UserImpl.h"


    using namespace std;
    using namespace Chat;

    class Client {
        public:
            Client(int, char*[]);
            void setUsername(const string&);
            void setPassword(const string&);
            void createUser();
            void createRoom() const;
            ~Client();
        private:
            string username;
            string password;
            UserPrx user;
            ServerPrx server;
            Ice::CommunicatorPtr iceCommunicator;
            Ice::ObjectAdapterPtr adapter;
    }; 

#endif