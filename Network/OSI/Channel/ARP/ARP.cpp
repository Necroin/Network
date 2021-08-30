#include "ARP.h"


ARP::ARP(MAC_t src_mac, MAC_t dest_mac, IP::Address src_ip, IP::Address dest_ip, int operation) :
	src_mac(src_mac),
	dest_mac(dest_mac),
	src_ip(src_ip),
	dest_ip(dest_ip),
	operation(operation)
{}

std::ostream& operator<<(std::ostream & out, const ARP & arp)
{
	std::cout << "ARP:" << std::endl
		<< "  Source MAC: " << arp.src_mac << std::endl
		<< "  Destination MAC: " << arp.dest_mac << std::endl
		<< "  Operation: " << arp.operation << std::endl;
	return out;
}
