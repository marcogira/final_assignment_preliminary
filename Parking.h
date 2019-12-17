#ifndef PARKING_H
#define PARKING_H

#include <ostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

#include "Access.h"
#include "Date.h"

using std::vector;
using std::list;
using std::string;

//Parking class
class Parking {
public:
	// constructors
	Parking(int capacity, float daily_fee, float hourly_fee);    // check for valid date and initialise
	Parking();                         // default constructor

	// getter functions
	int get_capacity() const;
	float get_daily_fee() const;
	float get_hourly_fee() const;
	vector <string> get_cars_parked() const;

	// methods
	void add_incoming_car( string licence_plate, Date access_time );
	void remove_outcoming_car( string licence_plate, Date exit_time );


private:
	int capacity;      // year
	float daily_fee;
	float hourly_fee;
	list <Access> parked_cars;
};

// operators
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
