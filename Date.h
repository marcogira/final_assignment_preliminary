
#ifndef DATE_H
#define DATE_H

#include <ostream>

// class date
class Date {
public:
	enum Month {
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	// constructors
	Date(int year, Month month, int day, int hour, int minute);    // initialize a new date with passe datas
	Date();                         // initialize a new data with default constructor

	//getter functions
	int get_year() const;
	Month get_month() const;
	int get_day() const;
	int get_hour() const;
	int get_minute() const;

private:

	//date class members
	int year;   
	Month month;
	int day;    
	int hour;   
	int minute; 
};

// operators
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif
