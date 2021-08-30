#pragma once
#ifndef _DEVICE_H_
#define _DEVICE_H_
#include "Components/Port/Port.h"
#include <map>
#include <string>
#include <vector>

class Device {
private:
	void update_arp_table_record(MAC_t my_port_mac, IP::Address ip, MAC_t mac);
	void insert_to_arp_table(MAC_t my_port_mac, IP::Address ip, MAC_t mac);
protected:
	std::map<MAC_t, std::list<std::pair<IP::Address, MAC_t>>> _arp_table;
	
	std::vector<Port> _ports;
	std::string _name;

	IP::Address _ip_addr;

	Port* find_port_from_MAC(MAC_t mac);

	std::shared_ptr<std::pair<MAC_t, std::pair<IP::Address, MAC_t>>> find_arp_table_record_from_ip(IP::Address ip_addr);

	void add_record_to_arp_table(MAC_t my_port_mac, IP::Address ip, MAC_t mac);

	virtual void handle_arp(ARP arp);
	virtual void handle_ip(IP ip);
	virtual void handle_icmp() {}
	virtual void handle_rip() {}
	virtual void handle_ospf() {}
public:
	Device(std::string name);
	std::vector<Port>& ports() { return _ports; }

	virtual void action();

	void start_expolre();
};
#endif