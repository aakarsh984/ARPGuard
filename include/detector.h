#ifndef DETECTOR_H
#define DETECTOR_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <cstdint>

class Detector
{
private:

    // Detection 3: Multiple IPs claimed by same MAC
    static std::unordered_map<
        std::string,
        std::unordered_set<std::string>
    > macToIPs;

public:
  // Detection 1: MAC conflict 
    static bool detectIpMacConflict(
        const std::string& oldMac,
        const std::string& newMac
    );



  // Detection 2: Gratuitous ARP
    // Gratuitous ARP = ARP Reply where senderIP == targetIP
 static bool isGratuitousArp(const std::string& senderIP,
                         const std::string& targetIP,
                         uint16_t opcode);

    // Detection 3: Broadcast MAC
    // No real device has MAC ff:ff:ff:ff:ff:ff
   static  bool isBroadcastMac(const std::string& mac);


    // Detection 4: One MAC claiming many IPs
    static bool detectMultipleIpsPerMac(
        const std::string& ip,
        const std::string& mac
    );

};

#endif
