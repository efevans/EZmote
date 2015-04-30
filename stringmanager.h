/*
 * Object for holding strings in a map
 * Contains methods for reading/writing map from/to file
 */

#ifndef HOTKEYSAVER_H
#define HOTKEYSAVER_H

#include <map>

class StringManager
{
public:
    StringManager();
    ~StringManager();

    std::string& operator [](std::string&);

private:
    std::map<std::string, std::string> stringHotKeys;
};

#endif // HOTKEYSAVER_H
