#include "machine_a_event.h"
#include "time_manipulation.h"
#include "machine_sim.h"
#include <iostream>

int main() {
	std::shared_ptr<machine_simulation> sim = std::make_shared<machine_simulation>(2, 2);
	int product_number = 1;
	std::string event_name;
	
	while (product_number <= 10) {
		event_name = "Product #";
		event_name = event_name.append(std::to_string(product_number++));
		sim->schedule_event(std::make_shared<machine_a_event>(event_name, get_random_time(1, 5), sim));
	}

	std::cout << "Controls:" << std::endl;
	std::cout << "s : Next Step" << std::endl;
	std::cout << "r : Run complete Simulation" << std::endl;
	std::cout << "p : Print results" << std::endl;
	std::cout << "q : Quit program" << std::endl;
	
	std::string input;
	std::cin >> input;

	while (!input.empty()) {
		if (input._Equal("s")) {
			sim->step();
		} else if (input._Equal("r")) {
			sim->run();
		} else if (input._Equal("p")) {
			sim->print_results();
		} else if (input._Equal("q")) {
			break;
		}
		std::cin >> input;
	}
	
	return 0;
}