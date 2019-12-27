#include <list>
using std::list;
#include <iterator>
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::istringstream;
#include <fstream>
using std::ifstream;
#include <thread>
using std::thread;

#include "Parking.h"
#include "Access.h"



int main()
{
	Parking parking1(100,1,1);
	//parking1.add_incoming_car( "park1_access.txt" );
	thread parking1_access_manager ( [ &parking1 ]() { parking1.add_incoming_car( "park1_access.txt" ); } );
	thread parking1_exit_manager ( [ &parking1 ]() { parking1.remove_outcoming_car( "park1_exit.txt" ); } );
	
	parking1_access_manager.join();
	parking1_exit_manager.join();
/*
	cout << "\n\nHERE YOU HAVE CARS STILL PARKED:" << endl;
	list <Access> parked_cars=parking1.get_parked_cars();
	for( std::list<Access>::iterator it=parked_cars.begin() ; it != parked_cars.end() ; it++ ){ //slides along register of arked cars 
		cout << "\n     " << it->get_licence_plate() << endl;
	}*/
  return 0;
}
