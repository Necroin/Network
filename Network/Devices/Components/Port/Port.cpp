#include "Port.h"

void Port::put(std::shared_ptr<Ethernet> channel_protocol)
{
	_input_buffer.emplace_back(channel_protocol);
}

Port::Port() : _connected_port(nullptr), _mac(_global_mac_counter)
{
	++_global_mac_counter;
}

bool Port::connect(Port& other)
{
	if (other._connected_port == nullptr) {
		if (_connected_port != nullptr) {
			_connected_port->_connected_port = nullptr;
		}
		_connected_port = &other;
		other._connected_port = this;
		return true;
	}
	return false;
}

void Port::send(std::shared_ptr<Ethernet> channel_protocol)
{
	if (_connected_port) {
		_connected_port->put(channel_protocol);
	}
}

std::shared_ptr<Ethernet> Port::get()
{
	if (_input_buffer.empty()) {
		return std::shared_ptr<Ethernet>();
	}
	auto packet = _input_buffer.front();
	_input_buffer.pop_front();
	return packet;
}

MAC_t Port::mac()
{
	return _mac;
}
