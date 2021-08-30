#pragma once
#ifndef _ICMP_H_
#define _ICMP_H_
#include <memory>
#include "../IP/IP.h"

class ICMP {
public:
	struct Type
	{
		struct ECHO_REPLY {
			inline static constexpr size_t value = 0;
		};
		struct DESTINATION_UNREACHABLE {
			inline static constexpr size_t value = 3;
			struct Code {
				inline static constexpr size_t net = 0;
				inline static constexpr size_t host = 1;
				inline static constexpr size_t protocol = 2;
				inline static constexpr size_t port = 3;
				inline static constexpr size_t df_set_fg_need = 4;
				inline static constexpr size_t source_root_failed = 5;
			};
		};
		struct REDIRECT {
			inline static constexpr size_t value = 5;
			struct Code {
				inline static constexpr size_t network = 0;
				inline static constexpr size_t host = 1;
				inline static constexpr size_t type_of_service_and_network = 2;
				inline static constexpr size_t type_of_service_and_host = 3;
			};
			struct Data {
				IP::Address ip;
			};
		};
		struct ECHO_REQUEST {
			inline static constexpr size_t value = 8;
			struct Code {
				inline static constexpr size_t _default = 0;
			};
		};
		struct TIME_EXCEEDED {
			inline static constexpr size_t value = 11;
			struct Code {
				inline static constexpr size_t code_ttl_expired = 0;
				inline static constexpr size_t not_all_fragments = 1;
			};
		};
	};
public:
	size_t type;
	size_t code;
	std::shared_ptr<void> data;

	ICMP(size_t type, size_t code, std::shared_ptr<void> data = std::shared_ptr<void>());

	friend std::ostream& operator << (std::ostream& out, const ICMP& icmp);
};
#endif