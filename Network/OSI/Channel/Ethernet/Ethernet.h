#pragma once
#ifndef _ETHERNET_H_
#define _ETHERNET_H_
#include <iostream>

using MAC_t = size_t;

class Ethernet {
public:
	inline static constexpr MAC_t BROADCAST_MAC = std::numeric_limits<MAC_t>::max();

	enum ProtocolType : size_t {
		IP = 1501,
		ARP,
		RIP,
		OSPF
	};

	size_t src_mac;
	size_t dest_mac;
	size_t length_or_type;
	std::shared_ptr<void> data;

	friend std::ostream& operator << (std::ostream& out, const Ethernet& ethernet);

	Ethernet(
		size_t src_mac,
		size_t dest_mac,
		size_t length_or_type,
		std::shared_ptr<void> data
	);
};
#endif