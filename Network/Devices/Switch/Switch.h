#pragma once
#ifndef _SWITCH_H_
#define _SWITCH_H_
#include "../Device.h"

class Switch : Device {
private:
	size_t _ports_number;
public:
	Switch(std::string name, size_t ports_number = 25);
	virtual void action() override;
	void connect(Port& port, size_t port_index);
};
#endif