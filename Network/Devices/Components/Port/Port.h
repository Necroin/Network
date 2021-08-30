#pragma once
#ifndef _PORT_H_
#define _PORT_H_
#include <exception>
#include <list>
#include "../../../OSI/osi_include.h"
#include <memory>

class Port {
private:
	inline static MAC_t _global_mac_counter = 1;
private:
	MAC_t _mac;
	std::list<std::shared_ptr<Ethernet>> _input_buffer;
	Port* _connected_port;
	void put(std::shared_ptr<Ethernet> channel_protocol);
public:
	Port();
	bool connect(Port& other);
	void send(std::shared_ptr<Ethernet> channel_protocol);
	std::shared_ptr<Ethernet> get();
	MAC_t mac();
};
#endif