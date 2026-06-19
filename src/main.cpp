#include "../include/sniffer.h"

int main()
{
    PacketSniffer sniffer;
    sniffer.listInterfaces();
    sniffer.startCapture("eth1");
    return 0;
}
