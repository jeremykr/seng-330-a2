#include <iostream>
#include <vector>
#include "equipment.h"
using namespace std;

int main () {
	// Initialize prototypes.
	Equipment * treadmill_prototype = new Treadmill();
	Equipment * weight_machine_prototype = new WeightMachine();
	// Variables for holding user input.
	int type;
	int id;
	// Vector holding user-created equipment.
	vector<Equipment*> eq;
	// Main loop.
	for (;;) {
	
		cout << "Create new equipment: Type 0 for Treadmill, 1 for Weight Machine." << endl;
		cin >> type;
		cout << "Create an ID (an integer) to identify the piece of equipment." << endl;
		cin >> id;
		
		if (type == 0) {
			eq.push_back(treadmill_prototype->clone());
			eq.back()->set_id(id);
			cout << "Created Treadmill with id " << id << "." << endl;
		} else if (type == 1) {
			eq.push_back(weight_machine_prototype->clone());
			eq.back()->set_id(id);
			cout << "Created Weight Machine with id " << id << "." << endl;
		}
	
	}
	
	delete treadmill_prototype;
	delete weight_machine_prototype;

}
