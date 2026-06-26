# ARPGuard
Real-time ARP Poisoning Detection Tool in C++
# ARPGuard

## Overview

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
# ARPGuard

## Overview

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

## Project Structure

```
ARPGuard/
│
├── build/
├── docs/
├── include/
│   ├── arptable.h
│   ├── detector.h
│   ├── gatewaytracker.h
│   ├── logger.h
│   ├── parser.h
│   └── sniffer.h
│
├── logs/
│   └── alerts.log
│
├── src/
│   ├── arptable.cpp
│   ├── detector.cpp
│   ├── gatewaytracker.cpp
│   ├── logger.cpp
│   ├── main.cpp
│   ├── parser.cpp
│   └── sniffer.cpp
│
├── tests/
├── CMakeLists.txt
└── README.md
```

---

## Project Architecture

```
Network Interface
        │
        ▼
 Packet Sniffer
        │
        ▼
 ARP Packet Parser
        │
        ▼
  Detection Engine
        │
        ├── IP-MAC Conflict Detection
        ├── Gratuitous ARP Detection
        ├── Broadcast MAC Detection
        ├── Multiple IPs per MAC Detection
        └── Gateway MAC Tracking
        │
        ▼
     Logger
        │
        ▼
 Console Output + alerts.log
```

---

## Detection Techniques

### 1. IP-MAC Conflict Detection

Detects when an already learned IP address suddenly maps to a different MAC address.

---

### 2. Gratuitous ARP Detection

Detects Gratuitous ARP packets where the sender advertises its own IP address without a request.

---

### 3. Broadcast MAC Detection

Raises a warning if an ARP packet claims a broadcast MAC address (`ff:ff:ff:ff:ff:ff`) as the sender.

---

### 4. Multiple IPs per MAC Detection

Monitors if one MAC address begins claiming multiple IP addresses, which can indicate spoofing activity.

---

### 5. Gateway MAC Monitoring

Learns the gateway's MAC address and reports any unexpected changes.

---

## Technologies Used

* C++17
* libpcap
* CMake
* Linux Networking APIs
* Kali Linux

---

## Build Instructions

### Install Dependencies

```bash
sudo apt update
sudo apt install build-essential cmake libpcap-dev
```

---

### Build

```bash
git clone https://github.com/<your-username>/ARPGuard.git

cd ARPGuard

mkdir build

cd build

cmake ..

make
```

---

### Run

```bash
sudo ./arpguard eth1
```

Replace `eth1` with your desired network interface.

---

## Sample Output

```
================================
ARP REPLY
================================
Sender IP  : 10.101.181.207
Sender MAC : 36:79:8c:e5:a1:89
Target IP  : 10.101.181.187
Target MAC : 08:00:27:41:76:d5

[ALERT]
IP-MAC Conflict

IP      : 10.101.181.207
Old MAC : aa:bb:cc:dd:ee:ff
New MAC : 36:79:8c:e5:a1:89
```

---

## Logging

All detected security events are automatically saved to:

```
logs/alerts.log
```

Each log entry includes:

* Timestamp
* Severity
* Detection Type
* IP Address
* MAC Address Information

---

## Current Status

### Completed

* Packet Capture
* ARP Packet Parsing
* ARP Table
* Detection Engine
* Gateway Tracking
* Logging Module

### In Progress

* Statistics Module
* Graceful Shutdown
* Configuration File
* Automatic Gateway Discovery

---

## Future Improvements

* Automatic Gateway Detection
* Rapid Remapping Detection
* ARP Reply Flood Detection
* Colored Terminal Output
* Configuration File Support
* JSON Log Export
* Unit Testing
* Docker Support

---

## Author

**Aakarsh Gupta**

B.Tech Artificial Intelligence & Data Science

Cybersecurity | Network Security | C++ | Linux

---

## License

This project is intended for educational and research purposes.


