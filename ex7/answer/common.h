#ifndef _COMMON_H
#define _COMMON_H

typedef unsigned PID;

enum PSTATE {
	P_READY,
	P_RUNNING,
	P_BLOCK,
	P_SLEEP,

	P_COUNT
};

static unsigned const MAX_PRIORITY = 99;

#endif

