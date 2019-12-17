#ifndef ACCESS_H
#define ACCESS_H

#include <ostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "Date.h"

using std::string;

//Access class
class Access {
public:
	// constructors
	Access(string licence_plate, Date access_time); //initialize a new access to parking
	Access();                         //initialize a default access to parking

	// getter functions
	string get_licence_plate() const;
	Date get_access_time() const;

	// methods
	void new_access(string licence_plate, Date access_time);

private:
	string licence_plate;      //licence plate of the incoming car
	Date access_time;      // date of the access
};

// operators
std::ostream& operator<<(std::ostream& os, const Access& access);

#endif
