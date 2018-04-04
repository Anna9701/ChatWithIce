#include <Ice/Ice.h>
#include "chat.h"

using namespace std;
using namespace Chat;

class UserI : public User {
    public:
        UserI(string n) : name(n){};
        virtual string getName(const Ice::Current&);
        virtual void SendMessage(const RoomPrx&, const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) {} //TODO
        virtual void SendPrivateMessage(const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) {}
    private:
        string name;
};

string UserI::getName(const Ice::Current&) { 
    return name;
}

int main(int argc, char* argv[]) {
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("SimpleUserAdapter", "default -p 10000");
        Ice::ObjectPtr object = new UserI("Sample");
        adapter->add(object, ic->stringToIdentity("SimpleUser"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const Ice::Exception& e) {
        cerr << e << endl;
        status = 1;
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    }
    if (ic) {
        try {
            ic->destroy();
        } catch (const Ice::Exception& e) {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}
