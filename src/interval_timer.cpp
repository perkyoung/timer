#include "interval_timer.h"

namespace arsenal {

IntervalTimer::~IntervalTimer() {
	std::list<TimerItem*>::iterator iter = timers_.begin(), iter_end = timers_.end();
	while(iter != iter_end) {
		delete *iter;
		iter++;
	}
}

int IntervalTimer::init() {
	int err = pthread_mutex_init(&cs_, 0);
	if(err != 0) {
		return -1;
	}

	err = pthread_cond_init(&cv_, 0);
	if(err != 0) {
		return -1;
	}

	is_stop_ = false;
	err = pthread_create(&timer_thread_id_, 0, thread_fun, this);
	if(err != 0) {
		return -1;
	}

	return 0;
}

int IntervalTimer::schedule(Task* t, const Timeval& delay, const Timeval& interval) {
	pthread_mutex_lock(&cs_);

	Timeval now;
	gettimeofday(now);
	TimerItem* timer_item = new TimerItem(t, interval, now + delay + interval);

	schedule(timer_item);

	pthread_cond_signal(&cv_);
	pthread_mutex_unlock(&cs_);
	return 0;
}

int IntervalTimer::destroy() {
	is_stop_ = true;
	pthread_cond_signal(&cv_);

	int err = pthread_join(timer_thread_id_, 0);
	if(err != 0) {
		return -1;
	}

	pthread_mutex_destroy(&cs_);
	pthread_cond_destroy(&cv_);
	return 0;
}

int IntervalTimer::wait_and_run() {
	while(!is_stop_) {
		Timeval now;
		gettimeofday(now);

		pthread_mutex_lock(&cs_);

		if(timers_.empty()) {
			//如果任务列表为空, 则等待
			pthread_cond_wait(&cv_, &cs_);
		} else {
			//如果不为空, 也会等待, 但是会有超时时间
			Timeval tv = timers_.front()->expire_;
			if(tv > now) {
				struct timespec tp;
				tp.tv_sec = tv.sec();
				tp.tv_nsec = tv.usec() * 1000;
				pthread_cond_timedwait(&cv_, &cs_, &tp);
			}
		}

		run_all_expire_task(now);

		pthread_mutex_unlock(&cs_);
	}
	pthread_exit(0);
}

void* IntervalTimer::thread_fun(void* arg) {
	IntervalTimer* timer = static_cast<IntervalTimer*> (arg);
	timer->wait_and_run();
	return NULL;
}

int IntervalTimer::run_all_expire_task(const Timeval& now) {

	std::list<TimerItem*>::iterator iter = timers_.begin(), iter_end = timers_.end();
	std::list<TimerItem*> new_task;

	while(iter !=iter_end) {
		if((*iter)->expire_ > now) {
			//任务已经排序, 第一个任务未超时, 则所有的都未超时
			break;
		}

		TimerItem* timer_item = *iter;
		timer_item->task_->run();
		if(timer_item->is_repeat()) {
			Timeval now;
			gettimeofday(now);
			TimerItem* temp = new TimerItem(timer_item->task_, timer_item->interval_, now + timer_item->interval_);
			new_task.push_back(temp);
		} else {
			delete timer_item;
		}
		timers_.erase(iter++);
	}

	iter = new_task.begin(), iter_end = new_task.end();
	while(iter !=iter_end) {
		schedule(*iter);
		iter++;
	}
	return 0;
}

int IntervalTimer::schedule(TimerItem* t) {
	std::list<TimerItem*>::iterator iter = timers_.begin(), iter_end = timers_.end();
	while(iter != iter_end) {
		if((*iter)->expire_ > t->expire_) {
			break;
		}
		iter++;
	}
	timers_.insert(iter, t);

	return 0;
}

}
