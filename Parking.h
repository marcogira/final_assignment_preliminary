#ifndef PARKING_H
#define PARKING_H

#include <ostream>
#include <list>
using std::list;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>
#include <mutex>  
using std::mutex; 
using std::unique_lock;      
#include <condition_variable>
using std::condition_variable;
#include <sstream>
using std::istringstream;
#include <fstream>
using std::ifstream;

#include "Access.h"
#include "Date.h"

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
	list <Access> get_parked_cars() const;

	// methods
	void add_incoming_car(string file_path);
	void remove_outcoming_car(string file_path);

private:
	int capacity;      // year
	float daily_fee;
	float hourly_fee;
	Date next_access_date{};
	Date next_exit_date{};
	list <Access> parked_cars;
	
	std::mutex mux; //mutex used to protect parked_cars to be written simultaneously from add_incoming_car & from remove_outcoming_car
	condition_variable access_turn; //condition variables used to get the correct execution order of file-reading threads 
	condition_variable exit_turn;
};

// operators
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
