#ifndef TIMER_TIMERITEM_H_
#define TIMER_TIMERITEM_H_

#include "task.h"
#include "timeval.h"

namespace arsenal {

struct TimerItem{
	TimerItem(Task* task, Timeval interval, Timeval expire)
			: task_(task), interval_(interval), expire_(expire) {
	}

	bool is_repeat() {
		if(interval_ > Timeval(0,0)) {
			return true;
		}
		return false;
	}

	Timeval expire_;
	Timeval interval_;
	Task* task_;
};
}

#endif /* TIMER_TIMERITEM_H_ */
