#include "DHCP.h"


DHCP::DHCP(Operation operation,
	size_t id,
	IP::Address ciaddr,
	IP::Address yiaddr,
	IP::Address siaddr,
	IP::Address giaddr,
	MAC_t chaddr,
	std::string sname,
	std::string file,
	DHCP_Type type
) :
	operation(operation),
	id(id),
	ciaddr(ciaddr),
	yiaddr(yiaddr),
	siaddr(siaddr),
	giaddr(giaddr),
	chaddr(chaddr),
	sname(sname),
	file(file),
	type(type)
{}