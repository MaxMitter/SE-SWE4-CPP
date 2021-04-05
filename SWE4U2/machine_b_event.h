#pragma once
#include <vector>
#include "event.h"
#include "machine_sim.h"

class machine_b_event : public machine_event {
public:
	machine_b_event(std::string name, std::time_t t, const std::shared_ptr<machine_simulation>& sim)
		: machine_event(name, t)
		, sim_ref{ sim } { }

	std::vector<std::shared_ptr<event>> process_event() override {
		sim_ref->b_done_processing();
		return std::vector<std::shared_ptr<event>>{};
	}

	std::vector<std::shared_ptr<event>> process_event(product& prod) override {
		prod.time_spent_b = m_time - prod.time_spent_buffer - prod.time_spent_a;
		return process_event();
	}

	std::string print_name() const override {
		return "Machine B: " + m_name;
	}

	private:
		const std::shared_ptr<machine_simulation>& sim_ref{ nullptr };
};
