# ARPGuard
Real-time ARP Poisoning Detection Tool in C++

ARPGuard is a C++-based network security tool that captures and analyzes ARP (Address Resolution Protocol) packets in real time to detect suspicious network behavior and possible ARP spoofing/poisoning attacks.

The project is built using **C++**, **libpcap**, and **CMake**, and runs on Linux (tested on Kali Linux).

---

## Features

* Real-time ARP packet capture using **libpcap**
* Parses ARP Requests and Replies
* Maintains an ARP table of IP → MAC mappings
* Detects possible ARP poisoning attacks
* Detects Gratuitous ARP packets
* Detects Broadcast MAC misuse
* Detects Multiple IPs mapped to a single MAC address
* Tracks Gateway MAC address
* Logs all security alerts with timestamps
* Modular architecture for future enhancements

---
## Author

**Aakarsh Gupta**

B.Tech Artificial Intelligence & Data Science

Cybersecurity | Network Security | C++ | Linux

---

## License

This project is intended for educational and research purposes.


