#include "stringmanager.h"

StringManager::StringManager()
{

}

StringManager::~StringManager()
{

}

std::string& StringManager::operator [](std::string &str)
{
    return this->stringHotKeys[str];
}
