#include "Ethernet.h"


std::ostream& operator<<(std::ostream& out, const Ethernet& ethernet)
{
	std::cout << "Ethernet:" << std::endl
		<< "  Source MAC: " << ethernet.src_mac << std::endl
		<< "  Destination MAC: " << ethernet.dest_mac << std::endl
		<< "  Type/length: " << ethernet.length_or_type << std::endl;
	return out;
}

Ethernet::Ethernet(size_t src_mac, size_t dest_mac, size_t length_or_type, std::shared_ptr<void> data) :
	src_mac(src_mac),
	dest_mac(dest_mac),
	length_or_type(length_or_type),
	data(data)
{}
