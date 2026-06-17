#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H

class PacketSniffer
{
public:
    void listInterfaces();
    void startCapture(const char* interfaceName);
};

#endif
