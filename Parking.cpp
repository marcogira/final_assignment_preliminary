#include <ostream>
#include <iostream>
#include <list>

#include "Parking.h"

using std::cerr;
using std::ostream;
using std::endl;
using std::cout;

// parking
Parking::Parking(int passed_capacity, float passed_daily_fee, float passed_hourly_fee)
	:capacity{passed_capacity},
	daily_fee{passed_daily_fee},
	hourly_fee{passed_hourly_fee}
{
	if (capacity<0)  {
		cerr << "invalid capacity!\n";
		exit(1);
	}

	if (daily_fee<0)  {
		cerr << "invalid daily fee!\n";
		exit(1);
	}

	if (hourly_fee<0)  {
		cerr << "invalid houly fee!\n";
		exit(1);
	}
}

Parking::Parking() //default constructor
	:capacity{0},
	daily_fee{0},
	hourly_fee{0}
{
}

// return parking's capacity
int Parking::get_capacity() const
{
	return capacity;
}

// return parking's daily fee
float Parking::get_daily_fee() const
{
	return daily_fee;
}

// return parking's hourly fee
float Parking::get_hourly_fee() const
{
	return hourly_fee;
}

//add to the parked car vector a new car if there is room for it
void Parking::add_incoming_car(string passed_licence_plate, Date passed_access_time)
{
	if( static_cast <int> ( parked_cars.size() ) >= capacity ) //if no room is available
		cout << "\n\n  --- NO PARKINGS AVAILABLE, SORRY FOR THE INCONVENIENCE! --- " << endl;
	else{ //if there is room available
		Access new_access=Access(passed_licence_plate, passed_access_time);
		parked_cars.push_back(new_access);
		cout << "\n\nCAR ENTERED: " << new_access << endl;
	}
}

//found and remove an outcoming car from register of parked cars.
void Parking::remove_outcoming_car(string passed_licence_plate, Date passed_exit_time)
{
	for( std::list<Access>::iterator it=parked_cars.begin() ; it != parked_cars.end() ; it++ ){ //slides along register of arked cars 
		if( it->get_licence_plate() == passed_licence_plate ){ //check if current car licence plate is the outcoming licence plate
			parked_cars.erase(it); //if so, removes licence plate
			cout << "\n\n--- THANK YOU, AND SEE YOU AGAIN! ---" <<endl;
			return;	//breaks for cycle
		}
	}
	cout << "\n\n--- YOUR CAR SEEMS NOT TO BE CORRECTLY CHECKED-IN. --- \n         --- PLEASE CONTACT AN OPERATOR ---" << endl;	
}

// operators
ostream& operator<<(ostream& os, const Parking& parking)
{
	return os << "\n\n     PARKING CAPACITY:  " << parking.get_capacity()
		<< "\n     PARKING DAILY FEE: " << parking.get_daily_fee()
		<< "\n     PARKING HOULY FEE: " << parking.get_hourly_fee();
}
