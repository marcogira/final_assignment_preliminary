#include <ostream>
#include <iostream>

#include "Date.h"

using std::ostream;
using std::cerr;

// initialize a new date with passed datas
Date::Date(int passed_year, int passed_month, int passed_day, int passed_hour, int passed_minute)
	:year{passed_year}, 
	month{passed_month},
	day{passed_day},
	hour{passed_hour},
	minute{passed_minute}
{
	if (month<1 || month>12 || day<1 || day>31 || hour<0 || hour>23 || minute<0 || minute>59 )  {
		cerr << "invalid date\n";
		exit(1);
	}
}

//generate a default date to be used in default constructor
const Date& default_date()
{
	static Date dd{2001,1,1,0,0};   // start of 21st century
	return dd;
}

//initialize a new date with default constructor
Date::Date()
	:year{default_date().get_year()},
	month{default_date().get_month()},
	day{default_date().get_day()},
	hour{default_date().get_hour()},
	minute{default_date().get_minute()}
{
}

// return year member from class date
int Date::get_year() const{
	return year;
}

// return month member from class date
int Date::get_month() const{
	return month;
}

// return day member from class date
int Date::get_day() const{
	return day;
}

//return hour member from class date
int Date::get_hour() const{
	return hour;
}

//return minute member from class date
int Date::get_minute() const{
	return minute;
}

void Date::set_date(Date passed_date){

	year = passed_date.get_year();
	month = passed_date.get_month();
	day = passed_date.get_day();
	hour = passed_date.get_hour();
	minute = passed_date.get_minute();
	
	if (month<1 || month>12 || day<1 || day>31 || hour<0 || hour>23 || minute<0 || minute>59 )  {
		cerr << "invalid date\n";
		exit(1);
	}
}

//compares dates. if date1 >= date2 returns true, otherwise returns false
bool compare_dates(Date date1, Date date2) {
	if     ( date1.get_year()   > date2.get_year()  )                                           return (true);
	else if( date1.get_year()  == date2.get_year()  && date1.get_month()  > date2.get_month() ) return (true);
	else if( date1.get_month() == date2.get_month() && date1.get_day()    > date2.get_day()   ) return (true);
	else if( date1.get_day()   == date2.get_day()   && date1.get_hour()   > date2.get_hour()  ) return (true);
	else if( date1.get_hour()  == date2.get_hour()  && date1.get_minute() > date2.get_minute()) return (true);

	else return(false);
}

// operators
ostream& operator<<(ostream& os, const Date& date)
{
	return os << "DATE:   " << date.get_year()
		<< " / " << date.get_month()
		<< " / " << date.get_day() 
		<< "     HOUR:   " << date.get_hour() 
		<< " : " << date.get_minute() ;
}
