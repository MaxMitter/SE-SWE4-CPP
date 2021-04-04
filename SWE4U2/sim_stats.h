#pragma once
#include <string>

class sim_stats {
	public:
		sim_stats() {}
};

class machine_stats : public sim_stats {
	public:
		machine_stats(std::string item_name)
			: m_item_name{ item_name } { }

		std::string m_item_name{};
		unsigned int time_spent_a{ 0 };
		unsigned int time_spent_b{ 0 };
		unsigned int time_spent_puffer{ 0 };
};