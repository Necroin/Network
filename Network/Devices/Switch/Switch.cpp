#include "Switch.h"

Switch::Switch(std::string name, size_t ports_number) : Device(name), _ports_number(ports_number)
{
	_ports.resize(ports_number);
}

void Switch::action()
{
	for (size_t get_port_index = 0; get_port_index < _ports_number; ++get_port_index) {
		while (decltype(auto) packet = _ports[get_port_index].get()) {
			for (size_t send_pot_index = 0; send_pot_index < _ports_number; ++send_pot_index) {
				if (get_port_index != send_pot_index) {
					_ports[send_pot_index].send(packet);
				}
			}
		}
	}
}

void Switch::connect(Port& port, size_t port_index)
{
	_ports[port_index].connect(port);
}
