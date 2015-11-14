#include <gtest/gtest.h>
#include "common.h"

TEST(EquipmentCloneTest, TreadmillCloneCorrect) {
	Equipment * t1 = treadmill_prototype->clone();
	ASSERT_EQ(0, t1->get_id());
	Equipment * t2 = t1->clone();
	ASSERT_EQ(t1->get_id(), t2->get_id());
}

TEST(EquipmentCloneTest, WeightMachineCloneCorrect) {
	Equipment * wm1 = weight_machine_prototype->clone();
	ASSERT_EQ(0, wm1->get_id());
	Equipment * wm2 = wm1->clone();
	ASSERT_EQ(wm1->get_id(), wm2->get_id());
}

TEST(FetchEquipmentTest, EquipmentCorrect) {
	MachineList ML;
	vector<Equipment*> v;
	
	for (int i = 0; i < 3; i++) {
		Machine * m = ML.add_machine();
		m->set_type(0);
		m->set_id(i);
	}
	for (int i = 3; i < 6; i++) {
		Machine * m = ML.add_machine();
		m->set_type(1);
		m->set_id(i);
	}

	get_equipment(ML, v);

	for (int i = 0; i < 3; i++) {
		ASSERT_EQ("Treadmill", v[i]->get_type());
		ASSERT_EQ(i, v[i]->get_id());
	}
	for (int i = 3; i < 6; i++) {
		ASSERT_EQ("Weight machine", v[i]->get_type());
		ASSERT_EQ(i, v[i]->get_id());
	}
} 

TEST(EquipmentCreateAndSetIDTest, TreadmillCorrectIDs) {
	Equipment * t1 = treadmill_prototype->clone();
	Equipment * t2 = treadmill_prototype->clone();
	Equipment * t3 = treadmill_prototype->clone();
	t1->set_id(1);
	t2->set_id(100);
	t3->set_id(3592);
	ASSERT_EQ(1, t1->get_id());
	ASSERT_EQ(100, t2->get_id());
	ASSERT_EQ(3592, t3->get_id());
}

TEST(EquipmentCreateAndSetIDTest, WeightMachineCorrectIDs) {
	Equipment * wm1 = weight_machine_prototype->clone();
	Equipment * wm2 = weight_machine_prototype->clone();
	Equipment * wm3 = weight_machine_prototype->clone();
	wm1->set_id(2);
	wm2->set_id(300);
	wm3->set_id(6882);
	ASSERT_EQ(2, wm1->get_id());
	ASSERT_EQ(300, wm2->get_id());
	ASSERT_EQ(6882, wm3->get_id());
}

TEST(UniqueIDsTest, UniqueIDs) {
	vector<Equipment*> v;

	v.push_back(treadmill_prototype->clone());
	v.back()->set_id(0);

	for (int i = 1; i < 3; i++) {
		v.push_back(treadmill_prototype->clone());
		ASSERT_EQ(true, test_unique_ID(i, v));
		v.back()->set_id(i);
	}

	for (int i = 3; i < 6; i++) {
		v.push_back(weight_machine_prototype->clone());
		ASSERT_EQ(true, test_unique_ID(i, v));
		v.back()->set_id(i);
	}
}

TEST(UniqueIDsTest, NonUniqueIDs) {
	vector<Equipment*> v;

	v.push_back(treadmill_prototype->clone());
	v.back()->set_id(0);
	
	for (int i = 0; i < 3; i++) {
		v.push_back(treadmill_prototype->clone());
		ASSERT_EQ(false, test_unique_ID(0, v));
		v.back()->set_id(0);
	}

	for (int i = 1; i < 4; i++) {
		v.push_back(weight_machine_prototype->clone());
		ASSERT_EQ(true, test_unique_ID(i, v));
		v.back()->set_id(i);
	}
}

int main(int argc, char ** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();	
}
