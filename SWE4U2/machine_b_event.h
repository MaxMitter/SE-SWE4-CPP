#pragma once
#include <vector>
#include "event.h"
#include "machine_sim.h"

class machine_b_event : public machine_event {
public:
	machine_b_event(std::string name, std::time_t t)
		: machine_event(name, t) { }

	std::vector<std::shared_ptr<event>> process_event() override {
		return std::vector<std::shared_ptr<event>>{};
	}

	std::vector<std::shared_ptr<event>> process_event(product& prod) override {
		prod.time_spent_b += time;
		return process_event();
	}

	std::string print_name() const override {
		return "Machine B: " + m_name;
	}
};
