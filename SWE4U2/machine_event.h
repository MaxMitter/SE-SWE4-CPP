#pragma once
#include "event.h"

struct product {
	std::string name{};
	unsigned int time_spent_a{ 0 };
	unsigned int time_spent_buffer{ 0 };
	unsigned int time_spent_b{ 0 };
};

class machine_event : public event {
	public:
		machine_event(std::string name, std::time_t t) : event(name, t) {}

		virtual ~machine_event() override = default;
	
		virtual std::vector<std::shared_ptr<event>> process_event() override = 0;

		virtual std::vector<std::shared_ptr<event>> process_event(product& prod) = 0;
};