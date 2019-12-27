#ifndef DATE_H
#define DATE_H

#include <ostream>

// class date
class Date {
public:

	// constructors
	Date(int year, int month, int day, int hour, int minute);    // initialize a new date with passe datas
	Date();                         // initialize a new data with default constructor

	//getter functions
	int get_year() const;
	int get_month() const;
	int get_day() const;
	int get_hour() const;
	int get_minute() const;
	
	//update date methods
	void set_date(Date passed_date);
	

private:
	//date class members
	int year;   
	int month;
	int day;    
	int hour;   
	int minute; 
};

bool compare_dates(Date date1, Date date2); //compares dates. if date1 > date2 returns true, otherwise returns false

// operators
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif
