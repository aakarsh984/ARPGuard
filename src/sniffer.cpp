#include "../include/detector.h"
#include "../include/gatewaytracker.h"
#include "../include/parser.h"
#include "../include/arptable.h"
#include "../include/sniffer.h"
#include <pcap.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdint>
#include <sstream>
#include <iomanip>

static Detector detector;
static ARPTable arpTable;
void packetHandler( u_char* user,const struct pcap_pkthdr* header,const u_char* packet){
		ArpInfo info = Parser::parseArpPacket(packet);
		
		  // Detection 2
    if(Detector::isGratuitousArp(
        info.senderIP,
        info.targetIP,
        info.opcode))
    {
        std::cout
            << "\n[WARNING] Gratuitous ARP Detected from "
            << info.senderIP
            << " (" << info.senderMAC << ")"
            << std::endl;
    }

    // Detection 3
    if(Detector::isBroadcastMac(
        info.senderMAC))
    {
        std::cout
            << "\n[WARNING] Broadcast MAC Used As Sender"
            << std::endl;
    }

    // Only learn from ARP replies
    if(info.opcode == 2)
    {
        arpTable.updateEntry(
            info.senderIP,
            info.senderMAC
        );

        // Detection 4
        if(Detector::detectMultipleIpsPerMac(
            info.senderIP,
            info.senderMAC))
        {
            std::cout
                << "\n[WARNING]"
                << "\nMAC Claiming Multiple IPs"
                << "\nMAC : "
                << info.senderMAC
                << std::endl;
        }

        // Gateway learning
        GatewayTracker::learnGatewayMac(
            info.senderIP,
            info.senderMAC
        );

        // Detection 5
        if(GatewayTracker::detectGatewayMacChange(
            info.senderIP,
            info.senderMAC))
        {
            std::cout
                << "\n[CRITICAL]"
                << "\nGateway MAC Changed!"
                << "\nGateway IP : "
                << info.senderIP
                << "\nKnown MAC  : "
                << GatewayTracker::getGatewayMAC()
                << "\nCurrent MAC: "
                << info.senderMAC
                << std::endl;
        }
    }
}//function end

void PacketSniffer::listInterfaces()
{
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        std::cerr << "Error: " << errbuf << std::endl;
        return;
    }

    std::cout << "\nAvailable Interfaces:\n" << std::endl;

    int count = 1;

    for (pcap_if_t *device = alldevs; device; device = device->next)
    {
        std::cout << count++ << ". ";

        if (device->name)
            std::cout << device->name;

        if (device->description)
            std::cout << " - " << device->description;

        std::cout << std::endl;
    }

    pcap_freealldevs(alldevs);
}
void PacketSniffer::startCapture(const char* interfaceName)
{
    char errbuf[PCAP_ERRBUF_SIZE];




    pcap_t* handle = pcap_open_live(
        interfaceName,
        BUFSIZ,
        1,
        1000,
        errbuf);

    if (!handle)
    {
        std::cerr << "Failed to open interface: "
                  << errbuf
                  << std::endl;
        return;
    }

    std::cout << "\nListening on "
              << interfaceName
              << "...\n"
              << std::endl;
struct bpf_program fp;

if (pcap_compile(handle, &fp, "arp", 1, PCAP_NETMASK_UNKNOWN) == -1)
{
    std::cerr << "Could not compile filter" << std::endl;
    return;
}

if (pcap_setfilter(handle, &fp) == -1)
{
    std::cerr << "Could not set filter" << std::endl;
    return;
}
pcap_freecode(&fp); 
    pcap_loop(handle, -1, packetHandler, nullptr);
    pcap_close(handle);
}

