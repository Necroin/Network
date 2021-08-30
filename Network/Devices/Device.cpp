#include "Device.h"

void Device::handle_ip(IP ip) {}

void Device::update_arp_table_record(MAC_t my_port_mac, IP::Address ip, MAC_t mac)
{
	decltype(auto) record_it = _arp_table.find(my_port_mac);
	decltype(auto) pair_it = std::find_if(record_it->second.begin(), record_it->second.end(), 
		[&ip = ip](std::pair<IP::Address, MAC_t>& pair) {return pair.first == ip; });
	pair_it->second = mac;
}

void Device::insert_to_arp_table(MAC_t my_port_mac, IP::Address ip, MAC_t mac)
{
	decltype(auto) record_it = _arp_table.find(my_port_mac);
	if (record_it != _arp_table.end()) {
		record_it->second.push_back({ ip,mac });
	}
	else {
		_arp_table.insert(std::pair{ my_port_mac, std::list{std::pair{ip, mac}} });
	}
}

Port* Device::find_port_from_MAC(MAC_t mac)
{
	for (auto&& port : _ports) {
		if (port.mac() == mac) {
			return &port;
		}
	}
	return nullptr;
}

std::shared_ptr<std::pair<MAC_t, std::pair<IP::Address, MAC_t>>> Device::find_arp_table_record_from_ip(IP::Address ip_addr)
{
	for (auto&& arp_table_pair : _arp_table) {
		for (auto&& dest_record : arp_table_pair.second) {
			if (dest_record.first == ip_addr) {
				return std::make_shared<std::pair<MAC_t, std::pair<IP::Address, MAC_t>>>(
					std::pair{ arp_table_pair.first, dest_record }
				);
			}
		}
	}
	return std::shared_ptr<std::pair<MAC_t, std::pair<IP::Address, MAC_t>>>();
}

void Device::add_record_to_arp_table(MAC_t my_port_mac, IP::Address ip, MAC_t mac)
{
	decltype(auto) arp_record = find_arp_table_record_from_ip(ip);
	if (arp_record) {
		auto my_port_mac_record = arp_record->first;
		auto mac_record = arp_record->second.second;
		if (my_port_mac_record == my_port_mac) {
			if (mac_record != mac) {
				update_arp_table_record(my_port_mac, ip, mac);
			}
			return;
		}
	}
	insert_to_arp_table(my_port_mac, ip, mac);
}


void Device::handle_arp(ARP arp) {}

Device::Device(std::string name) : _name(name)
{
}

void Device::action()
{
	for (auto&& port : _ports) {
		while (decltype(auto) packet = port.get()) {
			if (packet->dest_mac == port.mac() || packet->dest_mac == Ethernet::BROADCAST_MAC) {
				if (packet->length_or_type == Ethernet::ProtocolType::IP) {
					decltype(auto) ip = *static_cast<IP*>(packet->data.get());
					add_record_to_arp_table(port.mac(), ip.src_ip, packet->src_mac);
					handle_ip(ip);
				}
				if (packet->length_or_type == Ethernet::ProtocolType::ARP) {
					handle_arp(*static_cast<ARP*>(packet->data.get()));
				}
			}
		}
	}
}

void Device::start_expolre()
{
	for (auto&& port : _ports) {
		decltype(auto) explore_arp = std::make_shared<ARP>(
			port.mac(),
			0,
			_ip_addr,
			IP::Address::broadcast(),
			ARP::Operation::Request
		);

		decltype(auto) explore_packet = std::make_shared<Ethernet>(
			port.mac(),
			Ethernet::BROADCAST_MAC,
			Ethernet::ProtocolType::ARP,
			explore_arp
		);

		std::cout << "-------------------------------------------------------------------------" << std::endl;

		std::cout << "Device: " << _name << " send packet" << std::endl
			<< *explore_packet << std::endl
			<< *explore_arp << std::endl;

		std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;

		port.send(explore_packet);
	}
}
