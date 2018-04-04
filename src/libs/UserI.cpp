#include "UserI.h"

string UserI::getName(const Ice::Current&) { 
    return name;
}