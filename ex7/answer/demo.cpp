#include <iostream>
#include <string>
#include <set>

#include "priority_queue.h"

using namespace std;

int main()
{
	PriorityQueue que;
	set< PID> pushed;

	string msg = "\
COMMANDS:\n\
	push  id ready priority\n\
		ready is 0 or 1\n\
	ready id\n\
	pop\n";

	string cmd;
	while ( cout << msg, cin >> cmd) {
		if ( cmd == "push") {
			PID id;
			int ready;
			unsigned priority;
			cin >> id >> ready >> priority;
			if ( pushed.find( id) == pushed.end()) {
				que.push( id, ready ? P_READY : P_SLEEP, priority);
				pushed.insert( id);
			} else
				cerr << "Already pushed PID " << id << endl;
		} else if ( cmd == "ready") {
			PID id;
			cin >> id;
			que.set_ready( id);
		} else if ( cmd == "pop") {
			if ( que.empty())
				cerr << "Empty!" << endl;
			else {
				PID id = que.pop();
				pushed.erase( id);
				cerr << id << endl;
			}
		}
	}
	return 0;
}

