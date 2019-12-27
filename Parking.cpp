#include <ostream>
using std::ostream;
#include <iostream>
using std::endl;
using std::cout;
using std::cerr;
#include <list>
using std::list;
#include <mutex>  
using std::mutex; 
using std::unique_lock;      
#include <condition_variable>
using std::condition_variable;
#include <sstream>
using std::istringstream;
#include <fstream>
using std::ifstream;

#include "Parking.h"

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

//get cars still in parking
list <Access> Parking::get_parked_cars() const{
	return parked_cars;
}

//method to be run as thread in order to check if a new car has entered & register it
void Parking::add_incoming_car(string file_path, int parkingID){
	//read input file
	ifstream infile;
   	infile.open(file_path); //input file path containing entering cars accesses
   	
   	if (!infile.is_open()) {
      		cout << "\n\nerror opening the input file located in " << file_path <<endl; //prints error if unable to open file
      		exit(EXIT_FAILURE);
   	}

	cout << "\n\nopened the input file located in " << file_path <<endl;
	
  	string line;
   	while (getline(infile, line)){
    		istringstream iss(line);
    		int read_year, read_month, read_day, read_hour, read_minute; //datas to be read from file
    		string read_licence_plate;
    
    		if (!(iss >> read_licence_plate >> read_year >> read_month >> read_day >> read_hour >> read_minute)) { break; } // check read line structure
    		Date new_access_date(read_year, read_month, read_day, read_hour, read_minute); //create a new date with read datas
    		next_access_date.set_date( new_access_date ); //updates next access operation date to be processed
    		Access new_access = Access(read_licence_plate, new_access_date); //create a new Access local object before entering in CS
    		
    		std::unique_lock<mutex> parked_cars_mutex(mux); //create a lock guard to avoid parked_cars change size/position of elements while adding the access
    		if(compare_dates( next_access_date , next_exit_date) && !exits_reading_done){ //if next income time > next outcome_time new_exit must be processed before new_access
    			exit_turn.notify_one(); //notifies exits manager thread
    			access_turn.wait(parked_cars_mutex); //waits for the other thread to process new_exit(s) till next income time < next outcome_time 
    		}
		//when unlocked processes a new access
		if( static_cast <int> ( parked_cars.size() ) >= capacity ){ //if no room is available
			parked_cars_mutex.unlock(); //exit from CS
			cout << "\n\n\n\nPARKING# " << parkingID << endl; 
			cout << "\n\n       --- NO PARKINGS AVAILABLE, SORRY FOR THE INCONVENIENCE! --- " << new_access << endl; //print output
		}
		else{ //if there is room available
			parked_cars.push_back(new_access); //add car to parked_cars
			parked_cars_mutex.unlock(); //exit from CS
			cout << "\n\n\n\nPARKING# " << parkingID << endl; 
			cout << "\n\n                --- HAVE A NICE JOURNEY! ---" << new_access << endl; //print output to the user
		}
    	}
    	access_reading_done = true; //set flag to true before signaling, to avoid deadlock of the other thread
    	exit_turn.notify_one(); //notifies exits manager thread and let it finish its data processing
   	infile.close();//close input file
}

//method to be run as thread in order to check if a new car has gone & remove it
void Parking::remove_outcoming_car(string file_path, int parkingID){
	//read input file
	ifstream infile;
   	infile.open(file_path); //input file path containing entering cars accesses
   	
   	if (!infile.is_open()) {
      		cout << "\n\nerror opening the input file located in " << file_path <<endl; //prints error if unable to open file
      		exit(EXIT_FAILURE);
   	}
   	cout << "\n\nopened the input file located in " << file_path <<endl;

  	string line;
   	while (getline(infile, line)){
   		istringstream iss(line);
    		int read_year, read_month, read_day, read_hour, read_minute;//datas to be read from file
    		string read_licence_plate;
    		
    		if (!(iss >> read_licence_plate >> read_year >> read_month >> read_day >> read_hour >> read_minute)) { break; } // check read line structure

    		Date new_exit_date( read_year, read_month, read_day, read_hour, read_minute );//create a new date with read datas
    		next_exit_date.set_date( new_exit_date );//updates next exit operation date to be processed
    		Access new_exit = Access(read_licence_plate , new_exit_date );//create a new Access local object before entering in CS
    		bool found{false}; //create a bool variable to send the correct output to user while not using CS
    		    		 
    		std::unique_lock<mutex> parked_cars_mutex(mux); //create a new lock guard
    		if(!compare_dates( next_access_date , next_exit_date ) && !access_reading_done){ //if next outcome time>=next income time (giving priority to exits thread if date1= date2). if the other thread already finished, does not stop anymore
    			access_turn.notify_one(); //notifies exits manager thread
    			exit_turn.wait(parked_cars_mutex); //waits for the other thread to process acces(s) till next outcome time < next income time 
    		}
    		
    		std::list<Access>::iterator it=parked_cars.begin() ; //create an iterator used to look for the exiting licence plate 
		do{
			if( it->get_licence_plate() == read_licence_plate ){ //check if current car licence plate is the outcoming licence plate
				parked_cars.erase(it); //if so, removes licence plate
				found=true; //set found flag to true so that the correct utput will be displayed once out of CS
			}
			it++; //if licence plate is not found, increments iterator
		} while(  it != parked_cars.end() && found==false ); //slides along register of parked cars till reaches its end or finds exiting car
		
		parked_cars_mutex.unlock(); //exit from CS, then print output
		
		cout << "\n\n\n\nPARKING# " << parkingID << endl; 
		if(found) //if could not find licence plate throws an error to the user
			cout << "\n\n            --- THANK YOU, AND SEE YOU AGAIN! ---" << new_exit << endl;
		else
			cout << "\n\n  --- YOUR CAR SEEMS NOT TO BE CORRECTLY CHECKED-IN. --- \n           --- PLEASE CONTACT AN OPERATOR ---" << new_exit <<  endl;
    	}
    	exits_reading_done = true;//set flag to true before signaling, to avoid deadlock of the other thread
    	access_turn.notify_one(); //notifies access manager thread and let it finish its data processing
    	infile.close();//close input file
}

// operators
ostream& operator<<(ostream& os, const Parking& parking)
{
	return os << "\n\n     PARKING CAPACITY:  " << parking.get_capacity()
		<< "\n     PARKING DAILY FEE: " << parking.get_daily_fee()
		<< "\n     PARKING HOULY FEE: " << parking.get_hourly_fee();
}
