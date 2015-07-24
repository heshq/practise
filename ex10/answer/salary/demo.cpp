#include <iostream>
#include <string>

#include "salary.h"

using namespace std;

int main()
{
	Salary system;

	string cmd;
	string important_message =
"COMMAND FORMAT:\n"
"	rise	from_id  to_id  by_how_much\n"
"	query	id\n"
"Boss He, Long Live! Long Live! Long Long Live!!\n";
	
	while ( cout << important_message << endl, cin >> cmd) {
		if ( cmd == "rise") {
			size_t from, to;
			int how_much;
			cin >> from >> to >> how_much;
			system.rise( from, to, how_much);
		} else  if ( cmd == "query") {
			size_t id;
			cin >> id;
			if ( id < system.size)
				cout << "Salary : " << system.query( id) << endl;
		}
	}
	return 0;
}

