#pragma once
#include "simulation.h"
#include "machine_event.h"
#include <string>
#include <iomanip>

enum class machine_state { none, idle, processing };

class machine_simulation : public simulation {
	public:
	machine_simulation(unsigned int a_capacity, unsigned int puffer_capacity, unsigned int b_capacity)
		: simulation()
		, machine_a_capacity{ a_capacity }
		, buffer_capacity{ puffer_capacity }
		, machine_b_capacity{ b_capacity } {
		std::cout << "[SIM] Starting simulation" << std::endl;
	}

	void print_results() {
		const int name_width = 15;
		const int time_width = 10;
		const char separator = ' ';
		int total_a = 0;
		int total_buffer = 0;
		int total_b = 0;
		
		std::cout << std::right << std::setw(name_width) << std::setfill(separator) << "Name"         << "|";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << "Time spent A" << "|";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << "Time Buffer " << "|";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << "Time spent B" << "|";
		std::cout << std::endl;
		for (auto& prod : m_products) {
			std::cout << std::right << std::setw(name_width) << std::setfill(separator) << prod.name << "|";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << prod.time_spent_a << "|";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << prod.time_spent_buffer - prod.time_spent_a << "|";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << prod.time_spent_b - prod.time_spent_buffer << "|";
			std::cout << std::endl;

			total_a += prod.time_spent_a;
			total_buffer += prod.time_spent_buffer - prod.time_spent_a;
			total_b += prod.time_spent_b - prod.time_spent_buffer;
		}

		std::cout << std::right << std::setw(name_width) << std::setfill(separator) << "Averages" << "|";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << double(total_a) / m_products.size() << "|";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << double(total_buffer) / m_products.size() << "|";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << double(total_b) / m_products.size() << "|";
		std::cout << std::endl;
	}

	void schedule_event(const std::shared_ptr<event>& new_event) override {
		int const pos = find_product(new_event->name());
		if (pos == -1) {
			m_products.push_back(product{ new_event->name() });
		}
		
		active_queue.push(new_event);
	}

	bool fire_event() override {
		if (active_queue.empty()) {
			return true;
		}
		else {
			auto cur_event = active_queue.top();
			auto cur_machine_event = dynamic_pointer_cast<machine_event>(cur_event);
			std::cout << "[SIM][EVENT]: " << cur_event->print_name() << " [TIME] " << cur_event->get_time() << std::endl;
			active_queue.pop();

			int prod_nr = find_product(cur_event->name());
			std::vector<std::shared_ptr<event>> new_events = cur_machine_event->process_event(m_products[prod_nr]);
			
			sim_time += cur_event->get_time();
			for (const auto& ev : new_events) {
				active_queue.push(ev);
			}
			return false;
		}
	}

	bool a_is_idle() const { return a_state == machine_state::idle; }
	bool b_is_idle() const { return b_state == machine_state::idle; }

	bool a_has_capacity() const {
		return machine_a_capacity > 0;
	}
	
	bool b_has_capacity() const {
		return machine_b_capacity > 0;
	}

	void a_start_processing(const int n = 1) {
		machine_a_capacity -= n;
	}

	void a_done_processing(const int n = 1) {
		machine_a_capacity += n;
	}

	void b_start_processing(const int n = 1) {
		machine_b_capacity -= n;
	}

	void b_done_processing(const int n = 1) {
		machine_b_capacity += n;
	}

	void buffer_add(const int n = 1) {
		buffer_capacity -= n;
	}

	void buffer_remove(const int n = 1) {
		buffer_capacity += n;
	}

	private:
		int find_product(std::string name) {
			int curr = 0;
			while (curr < m_products.size()) {
				if (m_products[curr].name._Equal(name)) {
					return curr;
				} else {
					curr++;
				}
			}

			return -1;
		}
	
		unsigned int machine_a_capacity{};
		unsigned int buffer_capacity{};
		unsigned int machine_b_capacity{};
		machine_state a_state{ machine_state::idle };
		machine_state b_state{ machine_state::idle };
		std::vector<product> m_products{};
};