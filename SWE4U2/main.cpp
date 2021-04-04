#include "simulation.h"

int main() {
	simulation sim(10);
	for (int i = 1; i < 10; i++) {
		sim.schedule_event(std::make_shared<event>(i));
	}

	sim.print_queue();

	sim.run();

	sim.print_queue();
}