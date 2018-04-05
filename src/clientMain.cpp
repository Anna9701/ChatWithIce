#include "Client.h"
#include "ServerImpl.h"

using namespace std;

int main(int argc, char* argv[]) {
    int status = 0;
    Client client(argc, argv);
    string clientInput;

    cout << "Enter your username: " << endl;
    cin >> clientInput;
    client.setUsername(clientInput);
    cout << "Enter your password: " << endl;
    cin >> clientInput;
    client.setPassword(clientInput);

    client.sendUser();

    return status;
}