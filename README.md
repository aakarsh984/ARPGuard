# ARPGuard
Real-time ARP Poisoning Detection Tool in C++

> Real-time ARP Poisoning Detection Tool written in C++

ARP poisoning is one of the most common attacks on local networks. An attacker sends fake ARP replies to trick devices into sending their traffic through the attacker's machine — a classic Man-in-the-Middle setup. Most people on a network have no idea it's happening.

ARPGuard watches your network interface in real time, builds a trusted map of who owns which IP address, and immediately alerts you the moment something looks wrong.

Built from scratch in C++ using libpcap. No heavy frameworks, no GUI bloat — just a focused tool that does one thing well.

---

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
=======
## How it works

Every ARP packet that passes through your network interface gets analyzed through a 5-stage detection pipeline:

```
Network Interface (eth0 / eth1 / wlan0)
        │
        ▼
Packet Capture — libpcap captures raw ARP packets
        │
        ▼
ARP Parser — extracts sender IP, sender MAC, opcode
        │
        ▼
Detection Engine
        ├── IP-MAC Conflict         [ALERT]
        ├── Gratuitous ARP          [INFO]
        ├── Broadcast MAC           [WARNING]
        ├── Multiple IPs per MAC    [WARNING]
        └── Gateway MAC Change      [CRITICAL]
        │
        ▼
Logger — console alert + timestamped entry in logs/alerts.log
```

For a detailed breakdown of each detection algorithm, see [docs/detection.md](docs/detection.md).

---

## Detection Algorithms

| # | Detection | What it catches | Severity |
|---|-----------|-----------------|----------|
| 1 | IP-MAC Conflict | A known IP suddenly maps to a different MAC | ALERT |
| 2 | Gratuitous ARP | Unsolicited ARP replies — a common spoofing technique | INFO |
| 3 | Broadcast MAC | Sender using `ff:ff:ff:ff:ff:ff` as source MAC | WARNING |
| 4 | Multiple IPs per MAC | One MAC claiming ownership of many IPs | WARNING |
| 5 | Gateway MAC Monitoring | Any change to the default gateway's MAC address | CRITICAL |

Detection 5 is the most important — nearly every real ARP poisoning attack targets the gateway first.

---

## Requirements

- Linux (developed and tested on Kali Linux)
- g++ with C++17 support
- CMake 3.10 or higher
- pkg-config
- libpcap development headers
- Root privileges (required for raw packet capture)

```bash
sudo apt update
sudo apt install g++ cmake pkg-config libpcap-dev git -y
```

---

## Installation

```bash
git clone https://github.com/aakarsh984/ARPGuard.git
cd ARPGuard
```

Before building, open `src/main.cpp` and set your gateway IP:

```cpp
GatewayTracker::setGatewayIP("your.gateway.ip.here");
```

Then build using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The binary `arpguard` will be created inside the `build/` directory.

---

## Usage

```bash
sudo ./build/arpguard <interface>
```

Find your interface and gateway:

```bash
ip link show               # list interfaces
ip route | grep default    # find gateway IP
```

Example:

```bash
sudo ./build/arpguard eth1
```

---

## Example Output

Normal operation — learning the network:

```
Listening on eth1...

[NEW]  192.168.1.1    ->  aa:bb:cc:dd:ee:01
[NEW]  192.168.1.105  ->  aa:bb:cc:dd:ee:05
[NEW]  192.168.1.207  ->  36:79:8c:e5:a1:89
```

Attack detected:

```
=====================================
[CRITICAL] Gateway MAC Change
IP      : 192.168.1.1
Old MAC : aa:bb:cc:dd:ee:01
New MAC : 11:22:33:44:55:66
=====================================

=====================================
[ALERT] IP-MAC Conflict
IP      : 192.168.1.1
Old MAC : aa:bb:cc:dd:ee:01
New MAC : 11:22:33:44:55:66
=====================================
```

All alerts are also saved to `logs/alerts.log` with full timestamps.

---

## Project Structure

```
ARPGuard/
├── src/
│   ├── main.cpp            # Entry point, argument handling, gateway init
│   ├── sniffer.cpp          # libpcap capture loop, packet handler
│   ├── parser.cpp           # Raw bytes → ArpInfo struct
│   ├── arptable.cpp         # Trusted IP-MAC table
│   ├── detector.cpp         # Detection algorithms 1-4
│   ├── gatewaytracker.cpp   # Detection algorithm 5
│   └── logger.cpp           # Console + file logging
├── include/                  # Header files for all modules
├── logs/
│   └── alerts.log           # Runtime alert log (gitignored)
├── docs/
│   └── detection.md         # Detailed detection algorithm documentation
├── CMakeLists.txt
└── README.md
```

### Component Responsibilities

```
Component                Responsibility
---------------------------------------------------
PacketSniffer            Capture ARP packets
Parser                   Parse raw Ethernet/ARP frames
ARPTable                 Maintain IP → MAC mappings
Detector                 Apply detection algorithms
GatewayTracker           Monitor gateway integrity
Logger                   Record alerts to console and file
```

---

## Testing

You can simulate an ARP spoofing attack locally using `dsniff`:

```bash
sudo apt install dsniff

# In terminal 1 — run ARPGuard
sudo ./build/arpguard eth1

# In terminal 2 — simulate attack
sudo arpspoof -i eth1 -t <victim-ip> <gateway-ip>
```

ARPGuard should immediately fire a CRITICAL alert when the gateway MAC changes.

---

## Limitations

- Detection only, no active prevention or blocking
- Single interface monitoring at a time
- Gateway IP must be set manually in source before building
- Tested on Linux only

---

## Roadmap

- [ ] Automatic gateway discovery via `ip route`
- [ ] Command line argument for gateway IP
- [ ] Whitelist support for trusted devices
- [ ] Rapid MAC remapping detection
- [ ] JSON log export for SIEM integration
- [ ] ARP Reply flood detection

---


## Author

**Aakarsh Gupta**
B.Tech — Artificial Intelligence & Data Science
Interests: Cybersecurity · Network Security · C++ · Linux

---

## Disclaimer

This tool is built for educational purposes and authorized security testing only. Do not run it on networks you do not own or have explicit permission to test.
