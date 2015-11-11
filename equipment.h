class Equipment {

public:
	virtual Equipment * clone () = 0;
	virtual void set_id (int id) = 0;
	virtual int get_id () = 0;
	
};

class Treadmill : public Equipment {

public:
	Treadmill () { _id = 0; }
	Treadmill (int id) { _id = id; }
	Treadmill (Treadmill& t) { t._id = _id; }
	Treadmill * clone () { return new Treadmill(*this); }
	
	void set_id (int id) { _id = id; }
	int get_id () { return _id; }
	
private:
	int _id;
	
};

class WeightMachine : public Equipment {

public:
	WeightMachine () { _id = 0; }
	WeightMachine (int id) { _id = id; }
	WeightMachine (WeightMachine& wm) { wm._id = _id; }
	WeightMachine * clone () { return new WeightMachine(*this); }
	
	void set_id (int id) { _id = id; }
	int get_id () {return _id; }
	
private:
	int _id;
	
};
