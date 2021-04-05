#pragma once
#include "simulation.h"
#include "machine_event.h"
#include <string>
#include <iomanip>

class machine_simulation : public simulation {
	public:
	machine_simulation(unsigned int buffer_capacity, unsigned int b_capacity)
		: simulation()
		, buffer_capacity{ buffer_capacity }
		, machine_b_capacity{ b_capacity } { }

	virtual ~machine_simulation() override = default;

	void print_results() {
		const int name_width = 15;
		const int time_width = 15;
		const char separator = ' ';
		int total_a = 0;
		int total_buffer = 0;
		int total_b = 0;
		int total_all = 0;
		
		std::cout << std::right << std::setw(name_width) << std::setfill(separator) << "Name"         << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << "Time spent A" << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << " Time Buffer" << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << "Time spent B" << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << "       Total" << " |";
		std::cout << std::endl;
		std::cout << std::right << std::setw(name_width + 5 * time_width) << std::setfill('-') << "-" << std::endl;
		for (auto& prod : m_products) {
			int const total = prod.time_spent_a + prod.time_spent_buffer + prod.time_spent_b;
			std::cout << std::right << std::setw(name_width) << std::setfill(separator) << prod.name << " |";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << prod.time_spent_a << " |";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << prod.time_spent_buffer << " |";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << prod.time_spent_b << " |";
			std::cout << std::right << std::setw(time_width) << std::setfill(separator) << total << " |";
			std::cout << std::endl;

			total_a += prod.time_spent_a;
			total_buffer += prod.time_spent_buffer;
			total_b += prod.time_spent_b;
			total_all += total;
		}
		std::cout << std::right << std::setw(name_width + 5 * time_width) << std::setfill('-') << "-" << std::endl;
		std::cout << std::right << std::setw(name_width) << std::setfill(separator) << "Averages " << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << static_cast<double>(total_a) / m_products.size() << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << static_cast<double>(total_buffer) / m_products.size() << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << static_cast<double>(total_b) / m_products.size() << " |";
		std::cout << std::right << std::setw(time_width) << std::setfill(separator) << static_cast<double>(total_all) / m_products.size() << " |";
		std::cout << std::endl;
	}

	void schedule_event(const std::shared_ptr<event>& new_event) override {
		int const pos = find_product(new_event->name());
		if (pos == -1) {
			m_products.push_back(product{ new_event->name() });
		}
		
		active_queue.push(new_event);
	}

	bool fire_event(bool output = false) override {
		if (active_queue.empty()) {
			return true;
		}
		else {
			auto const cur_event = active_queue.top();
			auto cur_machine_event = dynamic_pointer_cast<machine_event>(cur_event);
			if (output)
				std::cout << "[SIM][EVENT]: " << cur_event->print_name() << " [TIME] " << cur_event->get_time() << std::endl;
			active_queue.pop();

			int const prod_nr = find_product(cur_event->name());
			std::vector<std::shared_ptr<event>> new_events = cur_machine_event->process_event(m_products[prod_nr]);
			
			for (const auto& ev : new_events) {
				active_queue.push(ev);
			}
			return false;
		}
	}
	
	bool b_has_capacity() const {
		return machine_b_capacity > 0;
	}

	bool buffer_has_capacity() const {
		return buffer_capacity > 0;
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
	
		unsigned int buffer_capacity{};
		unsigned int machine_b_capacity{};
		std::vector<product> m_products{};
};