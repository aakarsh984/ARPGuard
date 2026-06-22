#include "../include/arptable.h"
#include <iostream>

bool ARPTable::updateEntry(const std::string& ip, const std::string& mac)
{
    // Look up IP in table
    auto it = table.find(ip);

    // Case 1: IP not seen before — learn it, no conflict
    if (it == table.end())
    {
        table[ip] = mac;
        std::cout << "[NEW]  " << ip << "  ->  " << mac << std::endl;
        return false;
    }

    // Case 2: IP seen before, MAC matches — all good
    if (it->second == mac)
    {
        return false;
    }

    // Case 3: IP seen before, MAC is DIFFERENT — conflict!
    std::cout << "\n[ALERT] Possible ARP Poisoning Detected!"
              << "\n  IP      : " << ip
              << "\n  Old MAC : " << it->second
              << "\n  New MAC : " << mac
              << std::endl;

    return true;  // conflict detected
}
