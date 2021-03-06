#include <iostream>
#include "src/task.h"
#include "src/timeval.h"
#include "src/interval_timer.h"

using std::cout;
using std::endl;

class simple_task : public arsenal::Task {
public:
	virtual int run() {
		cout << "simple task" << endl;
		return 0;
	}

	virtual ~simple_task() { }
};

class hello_task : public arsenal::Task {
public:
	virtual int run() {
		cout << "hello task" << endl;
		return 0;
	}
	virtual ~hello_task() { }
};

int main() {
	arsenal::IntervalTimer timer;
	timer.init();

	simple_task* t = new simple_task();
	timer.schedule(t, arsenal::Timeval(0, 0), arsenal::Timeval(3, 0));

	hello_task* ht = new hello_task();
	timer.schedule(ht, arsenal::Timeval(0, 0), arsenal::Timeval(1, 0));

	sleep(5);
	timer.destroy();

	return 0;
}
