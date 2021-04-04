#pragma once
#include <memory>
#include <vld.h>

enum class event_state{passive, active, queued, pending, conditional, closed};

class event {
	public:
		event(unsigned int t = 0) 
			: time{ t }
			, state{ event_state::passive } {}

		~event() = default;

		bool operator< (const event& rhs) {
			return (this->time < rhs.time);
		}
		bool operator>(const event& rhs) {
			return (this->time > rhs.time);
		}

		virtual void processEvent() {};

		bool passive() { return state == event_state::passive; }
		bool active() { return state == event_state::active; }
		bool queued() { return state == event_state::queued; }
		bool pending() { return state == event_state::pending; }
		bool conditional() { return state == event_state::conditional; }
		bool closed() { return state == event_state::closed; }

		unsigned int get_time() const {
			return time;
		}

	private:
		event_state state;
		unsigned int time;
};

struct eventComparator {
	bool operator() (const std::shared_ptr<event> left, const std::shared_ptr<event> right) const {
		return (left->get_time() < right->get_time());
	}
};