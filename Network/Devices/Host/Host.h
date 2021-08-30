#pragma once
#ifndef _HOST_H_
#define _HOST_H_
#include "../Device.h"

class Host : public Device {

private:
	std::random_device random_device;
private:
	virtual void handle_arp(ARP arp) override;
	virtual void handle_ip(IP ip) override;

public:
	Host(std::string name);
	Port& port();
	virtual void action() override;
};
#endif