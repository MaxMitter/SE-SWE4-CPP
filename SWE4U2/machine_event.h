#pragma once
#include "event.h"

struct product {
	std::string name{};
	unsigned int time_spent_a{ 0 };
	unsigned int time_spent_b{ 0 };
	unsigned int time_spent_buffer{ 0 };
};

class machine_event : public event {
	public:
		machine_event(std::string name, std::time_t t) : event(name, t) {}

		virtual std::vector<std::shared_ptr<event>> process_event() override {
			return std::vector<std::shared_ptr<event>>{};
		}

		virtual std::vector<std::shared_ptr<event>> process_event(product& prod) = 0;
};