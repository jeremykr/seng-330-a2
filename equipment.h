class Equipment {
///
/// Provides a virtual clone function for implementing
/// the prototype design pattern, as well as virtual
/// getter and setter functions.
///
public:
	virtual Equipment * clone () = 0;
	virtual void set_id (int id) = 0;
	virtual int get_id () = 0;
	virtual const char * get_type() = 0;
	
};

class Treadmill : public Equipment {
///
/// The Treadmill class is a concrete implementation
/// of the Equipment class, and contains a private
/// member variable, id.
///
public:
	Treadmill () { _id = 0; }
	Treadmill (int id) { _id = id; }
	Treadmill (Treadmill& t) { _id = t._id; }
	Treadmill * clone () { return new Treadmill(*this); }
	
	void set_id (int id) { _id = id; }
	int get_id () { return _id; }
	const char * get_type() { return "Treadmill"; }
	
private:
	int _id;	// An integer that can be used to identify
			// the treadmill.
};

class WeightMachine : public Equipment {
///
/// The WeightMachine class is a concrete implementation
/// of the Equipment class, and contains a private member
/// variable, id.
///
public:
	WeightMachine () { _id = 0; }
	WeightMachine (int id) { _id = id; }
	WeightMachine (WeightMachine& wm) { _id = wm._id; }
	WeightMachine * clone () { return new WeightMachine(*this); }
	
	void set_id (int id) { _id = id; }
	int get_id () {return _id; }
	const char * get_type() { return "Weight machine"; }
	
private:
	int _id;	// An integer that can be used to identify
			// the weight machine.
	
};
