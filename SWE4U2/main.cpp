#include "machine_a_event.h"
#include "time_manipulation.h"
#include "machine_sim.h"
#include <iostream>

int main() {
	std::shared_ptr<machine_simulation> sim = std::make_shared<machine_simulation>(5, 10, 10);
	int product_number = 0;
	std::string event_name;
	
	while (product_number < 25) {
		event_name = "Product #";
		event_name = event_name.append(std::to_string(product_number++));
		sim->schedule_event(std::make_shared<machine_a_event>(event_name, get_random_time(1, 5), sim));
	}
	
	std::string input;
	std::cin >> input;

	while (!input.empty()) {
		if (input._Equal("s")) {
			sim->step();
		} else if (input._Equal("r")) {
			std::cout << "[SIM] Running Simulation..." << std::endl;
			sim->run();
			std::cout << "[SIM] Done simulating..." << std::endl;
		} else if (input._Equal("q")) {
			sim->print_results();
			break;
		}
		std::cin >> input;
	}
	

	return 0;
}