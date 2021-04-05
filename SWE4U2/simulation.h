#pragma once
#include <queue>
#include <iostream>
#include "event.h"

struct event_comparator {
	bool operator() (const std::shared_ptr<event>& left, const std::shared_ptr<event>& right) const {
		return (*left > *right);
	}
};

using prio_queue =	std::priority_queue<std::shared_ptr<event>,
					std::vector<std::shared_ptr<event>>,
					event_comparator>;

class simulation {
	public:
		simulation() = default;

		simulation(const std::initializer_list<std::shared_ptr<event>> init_list) {
			for (const auto& ev : init_list) {
				active_queue.push(ev);
			}
		}

		virtual ~simulation() = default;
	
		virtual void schedule_event(const std::shared_ptr<event>& new_event) {
			active_queue.push(new_event);
		}

		virtual void run(){
			std::cout << "[SIM] Starting simulation" << std::endl;
			bool stopped = fire_event();
			while (!stopped) {
				stopped = fire_event();
			}
			stop();
		}
		
		void step() {
			if (fire_event(true)) {
				stop();
			}
		}

		static void stop() {
			std::cout << "[SIM] Stopping simulation." << std::endl;
		}

	protected:

		virtual bool fire_event(bool output = false) {
			if (active_queue.empty()) {
				return true;
			} else {
				auto cur_event = active_queue.top();
				if (output)
					std::cout << "[SIM][EVENT]: " << cur_event->name() << " [TIME] " << cur_event->get_time() << std::endl;
				active_queue.pop();

				std::vector<std::shared_ptr<event>> new_events = cur_event->process_event();
				for (const auto& ev : new_events) {
					active_queue.push(ev);
				}
				return false;
			}
		}

		prio_queue active_queue;
};