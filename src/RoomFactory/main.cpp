#include "Factory.h"

using namespace RoomFactory;

int main(int argc, char* argv[]) {
    Factory factory;
    factory.registerRoomFactory();

    return 0;
}