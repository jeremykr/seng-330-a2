class Equipment {

public:

	virtual Equipment * clone () = 0;
	
}

class Treadmill : public Equipment {

public:

	Equipment * clone () { return new Treadmill; }
	
}

class WeightMachine : public Equipment {

public:

	Equipment * clone () { return new WeightMachine; }
	
}
