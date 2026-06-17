#include "../include/sniffer.h"

int main()
{
    PacketSniffer sniffer;
    sniffer.listInterfaces();
    sniffer.startCapture("eth0");
    return 0;
}
