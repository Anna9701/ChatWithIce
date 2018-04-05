#include "UserImpl.h"

string UserImpl::getName(const Ice::Current&) { 
    return name;
}