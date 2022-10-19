#include <iostream>
#include <mavsdk.h>
#include <memory>
#include <plugins/param/param.h>
#include <plugins/telemetry/telemetry.h>
#include <unistd.h>

const std::string COM_OBS_AVOID = "COM_OBS_AVOID";

int main() {
	auto msdk = std::make_shared<mavsdk::Mavsdk>();
	mavsdk::ConnectionResult result = msdk->add_any_connection("udp://0.0.0.0:14540");
	if (result != mavsdk::ConnectionResult::Success) {
		return -1;
	}

	auto systems = msdk->systems();

	int retryCount = 0;
	while (systems.size() <= 0 && retryCount < 5) {
		usleep(500);
		systems = msdk->systems();
		retryCount++;
	}

	if (retryCount >= 5) {
		return -1;
	}

	auto fcSystem = systems.front();

	if (fcSystem == nullptr) {
		return -1;
	}

	auto fcParam = std::make_unique<mavsdk::Param>(fcSystem);
	auto fcTelemetry = std::make_unique<mavsdk::Telemetry>(fcSystem);

	auto params = fcParam->get_all_params();

	int count = params.int_params.size();

	std::cout << std::to_string(count) << " int params" << std::endl;

	return 0;
};