#pragma once
#ifndef _IP_H_
#define _IP_H_
#include <iostream>
#include <random>

class IP {
public:
	enum class ProtocolType {
		ICMP,
		IGMP,
		TCP,
		UPD
	};
public:
	class Address_or_Mask {
	protected:
		inline static std::random_device random_device;
	public:
		uint8_t oct_1;
		uint8_t oct_2;
		uint8_t oct_3;
		uint8_t oct_4;

		Address_or_Mask();
		Address_or_Mask(uint8_t oct_1, uint8_t oct_2, uint8_t oct_3, uint8_t oct_4);

		Address_or_Mask operator&(Address_or_Mask other);

		bool operator == (Address_or_Mask other);

		friend std::ostream& operator << (std::ostream& out, const Address_or_Mask& addr_mask);
	};
public:
	class Address : public Address_or_Mask {
	public:
		Address();
		Address(uint8_t oct_1, uint8_t oct_2, uint8_t oct_3, uint8_t oct_4);
		static Address broadcast();
	};
	using NetMask = Address_or_Mask;

	class Flags {
	public:
		bool dont_fragment;
		bool more_fragments;
	};
public:
	size_t id;
	size_t TTL;
	Flags flags;
	ProtocolType protocol;
	Address src_ip;
	Address dest_ip;
	std::shared_ptr<void> data;
public:
	IP(size_t id,
		size_t TTL,
		Flags flags,
		ProtocolType protocol,
		Address src_ip,
		Address dest_ip,
		std::shared_ptr<void> data);

	friend std::ostream& operator << (std::ostream& out, const IP& ip);
};
#endif