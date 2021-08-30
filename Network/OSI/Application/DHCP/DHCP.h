#pragma once
#ifndef _DHCP_H_
#define _DHCP_H_
#include "../../Network/IP/IP.h"
#include "../../Channel/Ethernet/Ethernet.h"

class DHCP {
public:
	enum class Operation {
		BootRequest,
		BootReply
	};
	Operation operation;

	size_t id;

	IP::Address ciaddr;
	IP::Address yiaddr;
	IP::Address siaddr;
	IP::Address giaddr;
	MAC_t chaddr;

	std::string sname;
	std::string file;

	enum class DHCP_Type {
		DISCOVER,
		OFFER,
		REQUEST,
		DECLINE,
		ACK,
		NAK,
		RELEASE,
		INFORM
	};
	DHCP_Type type;

	DHCP(Operation operation,
		size_t id,
		IP::Address ciaddr,
		IP::Address yiaddr,
		IP::Address siaddr,
		IP::Address giaddr,
		MAC_t chaddr,
		std::string sname,
		std::string file,
		DHCP_Type type
	);
};
#endif	