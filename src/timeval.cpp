#include "timeval.h"

namespace arsenal {
Timeval::Timeval()
		:sec_(0), usec_(0) { }

Timeval::Timeval(time_t sec, time_t usec)
		:sec_(sec), usec_(usec) {
	normalize();
}

void Timeval::operator()(time_t sec, time_t usec) {
	sec_ = sec;
	usec_ = usec;
	normalize();
}

void Timeval::normalize() {
	const static int micro_sec_per_sec = 1000000;
	if (usec_<0) {
		while (sec_>0) {
			if (usec_>0) {
				break;
			}
			usec_ += micro_sec_per_sec;
			sec_--;
		}
	}

	if (sec_<0) {
		while (usec_>0) {
			if (sec_>0) {
				break;
			}
			usec_ -= micro_sec_per_sec;
			sec_++;
		}
	}
}

void gettimeofday(Timeval& now) {
	struct timeval temp;
	::gettimeofday(&temp, 0);
	now(temp.tv_sec, temp.tv_usec);
}


}