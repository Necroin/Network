#pragma once
#ifndef _ARP_H_
#define _ARP_H_
#include "../../Network/IP/IP.h"
#include "../Ethernet/Ethernet.h"

class ARP {
public:
	enum Operation {
		Request = 1,
		Response = 2
	};

	MAC_t src_mac;
	MAC_t dest_mac;

	IP::Address src_ip;
	IP::Address dest_ip;

	int operation;

	ARP(MAC_t src_mac, MAC_t dest_mac, IP::Address src_ip, IP::Address dest_ip, int operation);

	friend std::ostream& operator << (std::ostream& out, const ARP& arp);
};
#endif