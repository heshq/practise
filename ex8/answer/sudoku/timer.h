#ifndef _TIMER_H
#define _TIMER_H

#include <ctime>	// clock_t

class Timer {
	private:
		clock_t _begin, _end;
	public:
		void begin();
		void end();

		float seconds() const;
};

#endif

