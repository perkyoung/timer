#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <pthread.h>
#include <list>
#include "timeritem.h"
#include "task.h"
#include "timeval.h"

namespace arsenal {

class Timer {
public:
	~Timer();
	int init();
	int schedule(Task*, const Timeval&, const Timeval&);
	int destroy();
private:
	int schedule(TimerItem* );
	int wait_and_run();
	int run_all_expire_task(const Timeval& now);

	static void* thread_fun(void*);

	pthread_mutex_t cs_;
	pthread_cond_t cv_;
	pthread_t timer_thread_id_;

	bool is_stop_;
	std::list<TimerItem*> timers_;
};
}



#endif /* TIMER_TIMER_H_ */
