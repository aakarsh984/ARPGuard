#ifndef ARPTABLE_H
#define ARPTABLE_H

#include <unordered_map>
#include <string>

class ARPTable
{
private:
    std::unordered_map<std::string,std::string> table;

public:
    bool updateEntry(const std::string& ip,const std::string& mac);
};

#endif
