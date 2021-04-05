#pragma once
#include <random>

inline std::time_t get_random_time(const int min, const int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> const distr(min, max);

	return distr(gen);
}