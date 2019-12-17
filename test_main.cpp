#include "Parking.h"
#include <iostream>
#include <fstream>
using std::ifstream;

using namespace std;

int main()
{
	//initialization of parkings objects. parking(int capacity, float daily_fee, float hourly fee)
	Parking parking1(10,2,3); 
	Parking parking2(5,2,4);

	parking1.add_incoming_car("AB123CD",{2013,Date::oct,24,2,31});
	parking2.add_incoming_car("BB123CD",{2014,Date::oct,24,2,31});
	parking2.add_incoming_car("CB123CD",{2015,Date::oct,24,2,31});
	parking1.add_incoming_car("DB123CD",{2016,Date::oct,24,2,31});
	parking1.add_incoming_car("EB123CD",{2017,Date::oct,24,2,31});
	parking1.add_incoming_car("FB123CD",{2018,Date::oct,24,2,31});
	parking2.add_incoming_car("GB123CD",{2019,Date::oct,24,2,31});
	parking1.add_incoming_car("HB123CD",{2020,Date::oct,24,2,31});
	parking2.add_incoming_car("IB123CD",{2021,Date::oct,24,2,31});
	parking1.remove_outcoming_car("AB123CD",{2013,Date::oct,24,2,31});
	parking1.remove_outcoming_car("LB123CD",{2013,Date::oct,24,2,31});
	parking1.remove_outcoming_car("AB123CD",{2013,Date::oct,24,2,31});
	parking2.add_incoming_car("CB123FD",{2015,Date::oct,24,2,31});


  return 0;
}
