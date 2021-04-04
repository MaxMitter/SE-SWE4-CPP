#pragma once
#include <memory>
#include <string>
#include <vld.h>

class event {
	public:
		event(std::string& name, std::time_t t = 1) 
			: m_name{ name }
			, time{ t } {}

		friend bool operator< (const event& lhs, const event& rhs) {
			return (lhs.time < rhs.time);
		}
		friend bool operator> (const event& lhs, const event& rhs) {
			return (lhs.time > rhs.time);
		}

		virtual std::vector<std::shared_ptr<event>> process_event() = 0;

		std::time_t get_time() const {
			return time;
		}

		virtual std::string print_name() const {
			return m_name;
		}

		virtual std::string name() const {
			return m_name;
		}

	protected:
		std::string m_name;
		std::time_t time;
};

struct eventComparator {
	bool operator() (const std::shared_ptr<event>& left, const std::shared_ptr<event>& right) const {
		return (*left > *right);
	}
};