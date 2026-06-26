# Detection Algorithms

# ARPGuard Detection Engine

## Overview

The ARPGuard detection engine analyzes every captured ARP packet in real time and applies a series of detection rules to identify suspicious network behavior that may indicate ARP spoofing or ARP poisoning attacks.

Each captured packet follows the processing pipeline below:

```text
Network Interface
        │
        ▼
Packet Capture (libpcap)
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
        └── Gateway MAC Monitoring
        │
        ▼
Logger
```

---

# Detection Rule 1: IP-MAC Conflict Detection

## Objective

Detect when an IP address that has already been learned suddenly maps to a different MAC address.

This is one of the most common indicators of an ARP spoofing attack.

---

## Working

ARPGuard maintains an in-memory ARP table.

```
IP Address
        │
        ▼
MAC Address
```

Example:

```
10.101.181.207
        │
        ▼
36:79:8c:e5:a1:89
```

If another packet later claims

```
10.101.181.207
        │
        ▼
aa:bb:cc:dd:ee:ff
```

ARPGuard reports a possible spoofing attempt.

---

## Algorithm

```
if(IP not found)

        Learn mapping

else

        Compare stored MAC

        if(MAC changed)

                Raise ALERT
```

---

## Complexity

Time Complexity:

```
O(1)
```

Average-case lookup using `std::unordered_map`.

Space Complexity:

```
O(n)
```

where `n` is the number of learned hosts.

---

# Detection Rule 2: Gratuitous ARP Detection

## Objective

Detect Gratuitous ARP packets.

Gratuitous ARP packets are transmitted without a preceding ARP request and are used by devices to announce or verify their own IP address.

Although legitimate systems use Gratuitous ARP, attackers may abuse it to poison ARP caches.

---

## Detection Logic

ARPGuard identifies Gratuitous ARP packets using:

```
Opcode == ARP Reply

AND

Sender IP == Target IP
```

Example:

```
Sender IP : 192.168.1.20

Target IP : 192.168.1.20
```

---

## Algorithm

```
if(opcode == ARP_REPLY)

    if(senderIP == targetIP)

        Raise INFO
```

---

## Severity

```
INFO
```

A single Gratuitous ARP packet is not considered malicious.

---

# Detection Rule 3: Broadcast MAC Detection

## Objective

Detect invalid sender MAC addresses.

A sender MAC address should never be

```
ff:ff:ff:ff:ff:ff
```

This address is reserved as the Ethernet broadcast address.

---

## Detection Logic

```
if(senderMAC == ff:ff:ff:ff:ff:ff)

        Raise WARNING
```

---

## Severity

```
WARNING
```

---

# Detection Rule 4: Multiple IPs per MAC Detection

## Objective

Identify a MAC address claiming ownership of multiple IP addresses.

During ARP spoofing attacks, one attacker MAC may impersonate several hosts.

---

## Internal Data Structure

```
MAC Address
        │
        ▼
Set of IP Addresses
```

Implemented using

```
std::unordered_map<
    std::string,
    std::unordered_set<std::string>>
```

Example

```
AA:BB:CC:DD:EE:FF

↓

{
192.168.1.1

192.168.1.5

192.168.1.10
}
```

If the number of associated IPs exceeds a predefined threshold, ARPGuard reports suspicious behavior.

---

## Algorithm

```
Insert IP into MAC's IP set

if(size > Threshold)

        Raise WARNING
```

---

## Complexity

Insertion

```
O(1)
```

Average case.

---

# Detection Rule 5: Gateway MAC Monitoring

## Objective

Monitor the network gateway.

Most ARP poisoning attacks target the default gateway because intercepting gateway traffic allows attackers to perform Man-in-the-Middle (MITM) attacks.

---

## Learning Phase

The gateway IP is configured by the user.

When an ARP Reply from the gateway is first observed,

ARPGuard stores

```
Gateway IP

↓

Gateway MAC
```

---

## Monitoring Phase

Every future ARP Reply from the gateway is compared against the stored MAC.

```
if(currentGatewayMAC != storedGatewayMAC)

        Raise CRITICAL
```

---

## Severity

```
CRITICAL
```

Gateway impersonation is considered a high-priority security event.

---

# Logging

Every detection event is logged with

* Timestamp
* Severity
* Detection Type
* IP Address
* MAC Address Information

Example

```
====================================

Time:
2026-06-26 14:15:21

Severity:
ALERT

Detection:
IP-MAC Conflict

IP:
10.101.181.207

Old MAC:
36:79:8c:e5:a1:89

New MAC:
aa:bb:cc:dd:ee:ff

====================================
```

---

# Alert Levels

| Severity | Description                                |
| -------- | ------------------------------------------ |
| INFO     | Informational network event                |
| WARNING  | Suspicious behavior requiring attention    |
| ALERT    | Strong indication of possible ARP spoofing |
| CRITICAL | High-confidence attack against the gateway |

---

# Current Detection Summary

| Detection Rule         | Purpose                              | Severity |
| ---------------------- | ------------------------------------ | -------- |
| IP-MAC Conflict        | Detect changed MAC for a known IP    | ALERT    |
| Gratuitous ARP         | Detect unsolicited ARP replies       | INFO     |
| Broadcast MAC          | Detect invalid sender MAC            | WARNING  |
| Multiple IPs per MAC   | Detect one MAC claiming multiple IPs | WARNING  |
| Gateway MAC Monitoring | Detect gateway impersonation         | CRITICAL |

---

# Future Detection Algorithms

The following detection mechanisms are planned for future releases:

* Rapid MAC Remapping Detection
* ARP Reply Flood Detection
* Duplicate IP Detection
* Time-based Behavioral Analysis
* Automatic Gateway Discovery
* Whitelist-based Trusted Devices
* Export Logs in JSON Format
* Real-time Dashboard
