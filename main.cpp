#include <iostream>
#include <vector>
#include <fstream>
#include "equipment.h"
#include "machine_list.pb.h"
using namespace std;

enum eq_type { TREADMILL, WEIGHT_MACHINE };

// Initialize prototypes.
Equipment * treadmill_prototype = new Treadmill();
Equipment * weight_machine_prototype = new WeightMachine();

void get_equipment (const MachineList& m_list, vector<Equipment*>& v) {

	for (int i = 0; i < m_list.machine_size(); i++) {

		int type = m_list.machine(i).type();

		if (type == TREADMILL) {

			v.push_back(treadmill_prototype->clone());

		} else if (type == WEIGHT_MACHINE) {

			v.push_back(weight_machine_prototype->clone());

		}

		v.back()->set_id(m_list.machine(i).id());
	}

}

void print_equipment_list (const MachineList& m_list) {

	for (int i = 0; i < m_list.machine_size(); i++) {

		int type = m_list.machine(i).type();

		if (type == TREADMILL) {

			cout << "Treadmill"; 

		} else if (type == WEIGHT_MACHINE) {

			cout << "Weight machine";

		}
		cout << ", ID " << m_list.machine(i).id() << endl;
	}

}

int main (int argc, char * argv[]) {

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc != 2) {

		cout << "No path to storage file given." << endl;
		return -1;

	}

	MachineList machine_list;

	// Variables for holding user input.
	int type;
	int id;

	// Vector holding user-created equipment.
	vector<Equipment*> ev;

	// Read the list of created machines from file.
	fstream input(argv[1], ios::in | ios::binary);

	if (!input) {

		cout << argv[1] << ": File not found. Creating new file." << endl;

	} else if (!machine_list.ParseFromIstream(&input)) {

		cerr << "Failed to parse from equipment list." << endl;
		return -1;

	}
	
	// Create equipment objects from file and store in vector.
	get_equipment(machine_list, ev);

	// Main loop.
	for (;;) {
	
		cout << "Create new equipment: Type 0 for Treadmill, or 1 for Weight Machine." << endl;
		cout << "Other options: Type 2 to quit, or 3 to list all equipment." << endl;
		cout << ">> ";
		cin >> type;

		if (type == 2) {

			break;

		} else if (type == 3) {

			cout << endl;
			print_equipment_list(machine_list);
			cout << endl;
			continue;

		} else if (type > 3 || type < 0) {
			
			cout << "You have typed an invalid choice." << endl;
			continue;
		
		}

		cout << "Create an ID (an integer) to identify the piece of equipment." << endl;
		cout << ">> ";
		cin >> id;
		
		Machine* machine = machine_list.add_machine();

		if (type == TREADMILL) {

			ev.push_back(treadmill_prototype->clone());
			cout << "Created Treadmill"; 

		} else if (type == WEIGHT_MACHINE) {

			ev.push_back(weight_machine_prototype->clone());
			cout << "Created Weight Machine";

		}
		
		cout << " with ID " << id << "." << endl;

		ev.back()->set_id(id);
		machine->set_type(type);
		machine->set_id(id);
	
	}

	// Write equipment list to file.
	fstream output(argv[1], ios::out | ios::trunc | ios::binary);

	if (!machine_list.SerializeToOstream(&output)) {

		cerr << "Failed to write to equipment list." << endl;
		return -1;

	}
	
	// Cleanup.
	delete treadmill_prototype;
	delete weight_machine_prototype;
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
