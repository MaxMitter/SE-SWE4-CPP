#pragma once
#include <vector>
#include "event.h"
#include "machine_b_event.h"
#include "machine_sim.h"
#include "time_manipulation.h"

class buffer_event : public machine_event {
public:
	buffer_event(std::string name, std::time_t t, const std::shared_ptr<machine_simulation>& sim)
		: machine_event(name, t)
		, sim_ref{ sim } { }

	buffer_event(buffer_event* ev)
	: machine_event(ev->m_name, ev->m_time + get_random_time(1, 5))
		, sim_ref{ ev->sim_ref } { }

	std::vector<std::shared_ptr<event>> process_event() override {
		if (sim_ref->b_has_capacity()) {
			sim_ref->buffer_remove();
			sim_ref->b_start_processing();
			return std::vector<std::shared_ptr<event>>{std::make_shared<machine_b_event>(m_name, m_time + get_random_time(1, 5), sim_ref)};
		} else {
			return std::vector<std::shared_ptr<event>>{std::make_shared<buffer_event>(this)};
		}
	}

	std::vector<std::shared_ptr<event>> process_event(product& prod) override {
		auto ret = process_event();
		if (!ret.empty()) {
			prod.time_spent_buffer = m_time - prod.time_spent_a;
		}
		return ret;
	}

	std::string print_name() const override {
		return "Buffer:    " + m_name;
	}
	private:
		const std::shared_ptr<machine_simulation>& sim_ref{ nullptr };
};