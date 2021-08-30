#include "Host.h"


void Host::handle_arp(ARP arp)
{
	decltype(auto) arp_operation = arp.operation;
	if (arp_operation == ARP::Operation::Request) {
		if (arp.dest_ip == _ip_addr || arp.dest_ip == IP::Address::broadcast()) {
			decltype(auto) my_port = port();

			decltype(auto) response_arp = std::make_shared<ARP>(
				port().mac(),
				arp.src_mac,
				_ip_addr,
				arp.src_ip,
				ARP::Operation::Response
			);

			decltype(auto) response_ethernet = std::make_shared<Ethernet>(
				my_port.mac(),
				arp.src_mac,
				Ethernet::ProtocolType::ARP,
				response_arp
			);

			std::cout << "-------------------------------------------------------------------------" << std::endl;

			std::cout << "Host: " << _name << " send packet" << std::endl
				<< *response_ethernet << std::endl
				<< *response_arp << std::endl;

			std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;

			my_port.send(response_ethernet);
		}
	}
	if (arp_operation == ARP::Operation::Response) {
		if (arp.dest_ip == _ip_addr) {
			decltype(auto) my_mac = port().mac();
			decltype(auto) other_mac = arp.src_mac;
			decltype(auto) other_ip = arp.src_ip;
			add_record_to_arp_table(my_mac, other_ip, other_mac);

			std::cout << "-------------------------------------------------------------------------" << std::endl;

			std::cout << "Host: " << _name << " inserted to arp table MAC: " << my_mac << " { IP: " << other_ip << " MAC: " << other_mac << " }" << std::endl;

			std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;
		}
	}
}

void Host::handle_ip(IP ip)
{
	decltype(auto) my_port = port();
	if (ip.dest_ip == _ip_addr || ip.dest_ip == IP::Address::broadcast()) {
		if (ip.protocol == IP::ProtocolType::ICMP) {
			decltype(auto) icmp = *static_cast<ICMP*>(ip.data.get());
			if (icmp.type == ICMP::Type::ECHO_REQUEST::value) {
				decltype(auto) reply_icmp = std::make_shared<ICMP>(
					ICMP::Type::ECHO_REPLY::value,
					0
				);

				decltype(auto) reply_ip = std::make_shared<IP>(
					ip.id,
					128,
					IP::Flags(),
					IP::ProtocolType::ICMP,
					_ip_addr,
					ip.src_ip,
					reply_icmp
				);

				decltype(auto) arp_record = find_arp_table_record_from_ip(ip.src_ip);

				decltype(auto) reply_ethernet = std::make_shared<Ethernet>(
					my_port.mac(),
					arp_record->second.second,
					Ethernet::ProtocolType::IP,
					reply_ip
				);

				std::cout << "-------------------------------------------------------------------------" << std::endl;

				std::cout << "Host: " << _name << " send packet" << std::endl
					<< *reply_ethernet << std::endl
					<< *reply_ip << std::endl
					<< *reply_icmp << std::endl;

				std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;


				my_port.send(reply_ethernet);
			}
		}
	}
}

Host::Host(std::string name) : Device(name)
{
	_ports.emplace_back(Port());
}

Port& Host::port()
{
	return _ports.front();
}

void Host::action()
{
	Device::action();

	decltype(auto) my_port = port();

	decltype(auto) port_table_it = _arp_table.find(my_port.mac());
	if (port_table_it != _arp_table.end()) {

		decltype(auto) request_icmp = std::make_shared<ICMP>(
			ICMP::Type::ECHO_REQUEST::value,
			ICMP::Type::ECHO_REQUEST::Code::_default
			);

		std::uniform_int_distribution<size_t> int_dist(0);
		
		decltype(auto) port_table = port_table_it->second;

		for (auto&& record : port_table) {
			decltype(auto) request_ip = std::make_shared<IP>(
				int_dist(random_device),
				128,
				IP::Flags(),
				IP::ProtocolType::ICMP,
				_ip_addr,
				record.first,
				request_icmp
				);


			decltype(auto) request_ethernet = std::make_shared<Ethernet>(
				my_port.mac(),
				record.second,
				Ethernet::ProtocolType::IP,
				request_ip
				);


			std::cout << "-------------------------------------------------------------------------" << std::endl;

			std::cout << "Host: " << _name << " send packet" << std::endl
				<< *request_ethernet << std::endl
				<< *request_ip << std::endl
				<< *request_icmp << std::endl;

			std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;

			my_port.send(request_ethernet);
		}
	}
}
