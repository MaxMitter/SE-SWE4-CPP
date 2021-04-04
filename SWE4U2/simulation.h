#pragma once
#include <queue>
#include <iostream>
#include "event.h"

using prio_queue =	std::priority_queue<std::shared_ptr<event>,
					std::vector<std::shared_ptr<event>,
					std::allocator<std::shared_ptr<event>>>,
					eventComparator>;

class simulation {
	public:
		simulation(unsigned int t = 0) : sim_time{ t } {
			cur_time = 0;
		}

		~simulation(){

		}

		void schedule_event(std::shared_ptr<event> new_event) {
			active_queue.push(new_event);
		}

		void print_queue() {
			int size = active_queue.size();
			while (size-- > 0) {
				std::cout << active_queue.top()->get_time();
				active_queue.pop();
			}
		}

		void run(){
			while (!active_queue.empty()) {
				std::shared_ptr<event> next_event = active_queue.top();
				cur_time = next_event->get_time();
				next_event->processEvent();
				active_queue.pop();
			}
		}

	private:
		unsigned int sim_time;
		unsigned int cur_time;
		prio_queue active_queue;
};