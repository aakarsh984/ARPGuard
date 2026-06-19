#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstdint>

struct ArpHeader
{
    uint16_t hardwareType;
    uint16_t protocolType;
    uint8_t hardwareSize;
    uint8_t protocolSize;
    uint16_t opcode;

    uint8_t senderMac[6];
    uint8_t senderIP[4];

    uint8_t targetMac[6];
    uint8_t targetIP[4];
};

class Parser
{
public:
    static std::string macToString(const uint8_t mac[6]);
    static std::string ipToString(const uint8_t ip[4]);

    static void parseArpPacket(const u_char* packet);
};

#endif
