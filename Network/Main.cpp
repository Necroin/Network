#include "Devices/devices_include.h"
#include "OSI/osi_include.h"
#include <memory>

int main() {
	std::list<std::unique_ptr<Device>> devices;



	devices.emplace_back(std::make_unique<Host>("h1"));
	decltype(auto) host1 = devices.back();
	devices.emplace_back(std::make_unique<Host>("h2"));
	decltype(auto) host2 = devices.back();

	host1->ports().front().connect(host2->ports().front());

	int it_count = 10;


	for (auto&& device : devices) {
		device->start_expolre();
	}

	while (it_count--) {
		for (auto&& device : devices) {
			device->action();
		}
	}
	system("pause");
	return 0;
}