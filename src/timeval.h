#ifndef TIMER_TIMEVAL_H_
#define TIMER_TIMEVAL_H_

#include <sys/time.h>

namespace arsenal {
class Timeval {
public:
	Timeval();
	Timeval(time_t sec, time_t usec);

	time_t sec();
	time_t usec();
	Timeval operator+ (const Timeval& t);
	bool operator> (const Timeval& t);
	bool operator== (const Timeval& t);
	void operator()(time_t sec, time_t usec);

private:
	void normalize();

private:
	time_t sec_;
	time_t usec_;
};

void gettimeofday(Timeval& now);

inline time_t Timeval::sec() {
	return sec_;
}

inline time_t Timeval::usec() {
	return usec_;
}

inline Timeval Timeval::operator+ (const Timeval& t) {
	Timeval temp;
	temp.sec_ = sec_ + t.sec_;
	temp.usec_ = usec_ + t.usec_;
	temp.normalize();
	return temp;
}

inline bool Timeval::operator> (const Timeval& t) {
	return sec_ > t.sec_ || (sec_ == t.sec_ && usec_ > t.usec_);
}

inline bool Timeval::operator== (const Timeval& t) {
	return sec_ == t.sec_ && usec_ == t.usec_;
}

}



#endif /* TIMER_TIMEVAL_H_ */
