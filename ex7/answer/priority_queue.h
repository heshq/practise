#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include "common.h"

class PriorityQueueImpl;

class PriorityQueue {
	private:
		PriorityQueueImpl *_impl;
	public:
		PriorityQueue();
		~PriorityQueue();

		void push( PID id, PSTATE state, unsigned priority);
		void set_ready( PID id);

		// IMPORTANT: must check empty() before calling pop()
		PID pop();
		bool empty();
};

#endif


