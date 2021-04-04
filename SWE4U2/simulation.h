#pragma once
#include <queue>
#include <iostream>
#include "event.h"

using prio_queue =	std::priority_queue<std::shared_ptr<event>,
					std::vector<std::shared_ptr<event>>,
					eventComparator>;

class simulation {
	public:
		simulation() = default;

		simulation(const std::initializer_list<std::shared_ptr<event>> init_list) {
			for (const auto& ev : init_list) {
				active_queue.push(ev);
			}
		}
	
		virtual void schedule_event(const std::shared_ptr<event>& new_event) {
			active_queue.push(new_event);
		}

		virtual void run(){
			bool stopped = fire_event();
			while (!stopped) {
				stopped = fire_event();
			}
			stop();
		}
		
		void step() {
			if (fire_event()) {
				stop();
			}
		}

		static void stop() {
			std::cout << "[SIM] Stopping simulation." << std::endl;
		}

	protected:
		prio_queue active_queue;

		virtual bool fire_event() {
			if (active_queue.empty()) {
				return true;
			} else {
				auto cur_event = active_queue.top();
				std::cout << "[SIM][EVENT]: " << cur_event->name() << " [TIME] " << cur_event->get_time() << std::endl;
				active_queue.pop();

				std::vector<std::shared_ptr<event>> new_events = cur_event->process_event();
				sim_time += cur_event->get_time();
				for (const auto& ev : new_events) {
					active_queue.push(ev);
				}
				return false;
			}
		}

		unsigned int sim_time{ 0 };
};