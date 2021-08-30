#include "IP.h"

IP::Address_or_Mask::Address_or_Mask(uint8_t oct_1, uint8_t oct_2, uint8_t oct_3, uint8_t oct_4) :
	oct_1(oct_1),
	oct_2(oct_2),
	oct_3(oct_3),
	oct_4(oct_4)
{}

IP::Address_or_Mask::Address_or_Mask() : 
	oct_1(0),
	oct_2(0),
	oct_3(0),
	oct_4(0)
{}

IP::Address_or_Mask IP::Address_or_Mask::operator&(Address_or_Mask other)
{
	return Address_or_Mask(
		oct_1 & other.oct_1,
		oct_2 & other.oct_2,
		oct_3 & other.oct_3,
		oct_4 & other.oct_4
	);
}

bool IP::Address_or_Mask::operator==(Address_or_Mask other)
{
	return oct_1 == other.oct_1 && oct_2 == other.oct_2 && oct_3 == other.oct_3 && oct_4 == other.oct_4;
}

IP::Address::Address() : Address_or_Mask()
{
	std::uniform_int_distribution<> int_distribution(0, 255);
	oct_1 = int_distribution(random_device);
	oct_2 = int_distribution(random_device);
	oct_3 = int_distribution(random_device);
	oct_4 = int_distribution(random_device);
}

IP::Address::Address(uint8_t oct_1, uint8_t oct_2, uint8_t oct_3, uint8_t oct_4) :
	Address_or_Mask(oct_1, oct_2, oct_3, oct_4)
{}

IP::Address IP::Address::broadcast()
{
	return Address(255, 255, 255, 255);
}

IP::IP(size_t id,
	size_t TTL,
	Flags flags,
	ProtocolType protocol,
	Address src_ip,
	Address dest_ip,
	std::shared_ptr<void> data
) : 
	id(id),
	TTL(TTL),
	flags(flags),
	protocol(protocol),
	src_ip(src_ip),
	dest_ip(dest_ip),
	data(data)
{}

std::ostream& operator<<(std::ostream& out, const IP::Address_or_Mask& addr_mask)
{
	out << (unsigned)addr_mask.oct_1 << "." 
		<< (unsigned)addr_mask.oct_2 << "." 
		<< (unsigned)addr_mask.oct_3 << "." 
		<< (unsigned)addr_mask.oct_4;
	return out;
}

std::ostream& operator<<(std::ostream& out, const IP& ip)
{
	out << "IP:" << std::endl
		<< "  id: " << ip.id << std::endl
		<< "  TTL: " << ip.TTL << std::endl
		<< "  Flags : { DF :" << ip.flags.dont_fragment << ", MF: " << ip.flags.more_fragments << " }" << std::endl
		<< "  Protocol" << std::endl
		<< "  Source IP: " << ip.src_ip << std::endl
		<< "  Destination IP: " << ip.dest_ip << std::endl;

	return out;
}
