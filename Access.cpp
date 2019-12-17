#include <ostream>
#include <iostream>
#include <string>

#include "Date.h"
#include "Access.h"

using std::cerr;
using std::ostream;

// initialize a new access with passed datas
Access::Access(string passed_licence_plate, Date passed_access_time)
	:licence_plate{passed_licence_plate}, access_time{passed_access_time}
{
}

//initialize a new access with default constructor: uses a standard licence plate and the default constructor for the date class
Access::Access()
	:licence_plate{"AA000AA"}, access_time{Date()}
{
}

// return licence plate member from class access
string Access::get_licence_plate() const
{
	return licence_plate;
}

// return access time member from class access
Date Access::get_access_time() const
{
	return access_time;
}


// operators
ostream& operator<<(ostream& os, const Access& access)
{
	return os << "\n\n     LICENCE PLATE: " << access.get_licence_plate()
		<< "\n     ACCESS TIME:   " << access.get_access_time() ;
}
