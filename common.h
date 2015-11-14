#pragma once
#include <iostream>
#include <vector>
#include "equipment.h"
#include "machine_list.pb.h"
using namespace std;

/// \file

enum eq_type { TREADMILL, WEIGHT_MACHINE, QUIT, LIST_EQUIPMENT };

// Initialize prototypes.
Equipment * treadmill_prototype = new Treadmill();
Equipment * weight_machine_prototype = new WeightMachine();

void get_equipment (const MachineList& m_list, vector<Equipment*>& v) {
///
/// The get_equipment function reads the MachineList object retrieved from the
/// buffer file and recreates each object using the information in the list.
/// Each object is then stored in a vector for use within the program.
///
/// \param m_list	:	The list of equipment read from the protocol buffer.
/// \param v		:	The vector where the equipment objects will be stored
///				for use in the program.
///

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
///
/// The print_equipment_list function reads the equipment stored in the MachineList
/// buffer object and prints out the type and ID of each piece of equipment currently
/// active within the program.	
///
/// \param m_list	:	The list of equipment read from the protocol buffer.
///


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

bool test_unique_ID (int id, const vector<Equipment*> v) {
///
/// Test the given ID to make sure that it is unique in the
/// list of active equipment.
///
/// \param id	:	The give ID of the machine.
/// \param v	:	A vector holding the list of equipment
///			active within the program.
///
	for (int i = 0; i < v.size(); i++) {

		if (id == v[i]->get_id()) {
		
			return false;
		
		}
	}
	return true;
}
