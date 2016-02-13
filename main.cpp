#include <iostream>
#include "task.h"
#include "timer.h"
#include "timeval.h"

using namespace std;

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
	simple_task* t = new simple_task();
	arsenal::Timer timer;
	timer.init();
	timer.schedule(t, arsenal::Timeval(0, 0), arsenal::Timeval(3, 0));

	hello_task* ht = new hello_task();
	timer.schedule(ht, arsenal::Timeval(0, 0), arsenal::Timeval(1, 0));

	while(1) {
		sleep(1);
	}
	return 0;
}