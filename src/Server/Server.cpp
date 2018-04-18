#include <Ice/Ice.h>
#include "chat.h"
#include "ServerImpl.h"
#include "PortsUtil.h"

using namespace LibsIce;
using namespace std;

int main(int argc, char* argv[]) {
    int status = 0;
    PortsUtil portsUtil;
    Ice::CommunicatorPtr iceCommunicator;
    try {
        iceCommunicator = Ice::initialize(argc, argv);
        int serverPort = portsUtil.getServerPort();
        Ice::ObjectAdapterPtr adapter = iceCommunicator->createObjectAdapterWithEndpoints("ServerAdapter", "default -p " + to_string(serverPort));
        Ice::ObjectPtr object = new ServerImpl();
        adapter->add(object, iceCommunicator->stringToIdentity("Server"));
        adapter->activate();
        iceCommunicator->waitForShutdown();
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    } catch (const RoomAlreadyExist &ex) {
        cerr << ex << endl;
    } catch (const NoSuchRoomExist& ex) {
            cerr << ex << endl;
    } catch (const UserAlreadyExists& ex) {
            cerr << "Such userr already exist" << endl;
    } catch (const Ice::Exception& e) {
        cerr << e << endl;
        status = 1;
    } 
    if (iceCommunicator) {
        try {
            iceCommunicator->destroy();
        } catch (const Ice::Exception& e) {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}
