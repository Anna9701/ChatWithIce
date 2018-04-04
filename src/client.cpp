#include <Ice/Ice.h>
#include "chat.h"

using namespace std;
using namespace Chat;

int main(int argc, char* argv[]) {
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("SimpleUser:default -p 10000");
        UserPrx user = UserPrx::checkedCast(base);
        if (!user)
            throw "Invalid proxy";
        cout << user->getName() << endl;
    } catch (const Ice::Exception& ex) {
        cerr << ex << endl;
        status = 1;
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    }

    if (ic)
        ic->destroy();

    return status;
}