#pragma once
#include <memory>
#include <string>
#include <vld.h>

class event {
	public:
		event(std::string& name, std::time_t t = 1) 
			: m_name{ name }
			, m_time{ t } {}

		virtual ~event() = default;

		friend bool operator< (const event& lhs, const event& rhs) {
			return (lhs.m_time < rhs.m_time);
		}
		friend bool operator> (const event& lhs, const event& rhs) {
			return (lhs.m_time > rhs.m_time);
		}

		virtual std::vector<std::shared_ptr<event>> process_event() = 0;

		std::time_t get_time() const {
			return m_time;
		}

		virtual std::string print_name() const {
			return m_name;
		}

		virtual std::string name() const {
			return m_name;
		}

	protected:
		std::string m_name;
		std::time_t m_time;
};