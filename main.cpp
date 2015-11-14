#include <fstream>
#include "common.h"

using namespace std;

/// \file

int main (int argc, char * argv[]) {

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc != 2) {

		cout << "Usage : ./main <buffer_file>" << endl;
		return -1;

	}

	MachineList machine_list;

	int type;	// Stores the user's input option 
			// (can be 0, 1, 2, or 3).
	int id;		// Stores the ID the user wishes to give
			// to a piece of equipment.

	vector<Equipment*> ev;	// Vector holding user-created equipment.

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

		if (type == QUIT) {
		// User wishes to quit.
			break;

		} else if (type == LIST_EQUIPMENT) {
		// User wishes to see list of objects currently
		// in use by the program.
			cout << endl;
			print_equipment_list(machine_list);
			cout << endl;
			continue;

		} else if (type > 3 || type < 0) {
		// User enters an invalid choice.
			cout << "You have typed an invalid choice." << endl;
			continue;
		
		}

		bool unique = false;
		
		while (!unique) {

			cout << "Create an ID (an integer) to identify the piece of equipment." << endl;
			cout << ">> ";
			cin >> id;

			if (!(unique = test_unique_ID(id, ev))) {

				cout << "That ID has already been assigned to another piece of equipment." << endl;
			
			}
		}
		
		Machine* machine = machine_list.add_machine();

		if (type == TREADMILL) {
		// Create new Treadmill object.
			ev.push_back(treadmill_prototype->clone());
			cout << "Created Treadmill"; 

		} else if (type == WEIGHT_MACHINE) {
		// Create new WeightMachine object.
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
