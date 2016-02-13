#ifndef TIMER_TASK_H_
#define TIMER_TASK_H_

namespace arsenal {
class Task {
public:
	virtual ~Task() { }
	virtual int run() = 0;
};
}

#endif /* TIMER_TASK_H_ */
