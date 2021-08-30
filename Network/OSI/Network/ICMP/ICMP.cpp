#include "ICMP.h"


ICMP::ICMP(size_t type, size_t code, std::shared_ptr<void> data) :
	type(type),
	code(code),
	data(data)
{}

std::ostream& operator<<(std::ostream & out, const ICMP & icmp)
{
	out << "ICMP:" << std::endl
		<< "  Type: " << icmp.type << std::endl
		<< "  Code: " << icmp.code << std::endl;
	return out;
}
