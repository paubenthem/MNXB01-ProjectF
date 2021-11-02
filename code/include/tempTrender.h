#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
class tempTrender {
	public:
	explicit tempTrender(const std::string& filePath); //Construct using the specified file
	~tempTrender() {} //Destructor

	// void tempOnDay(int monthToCalculate, int dayToCalculate) const; //Make a histogram of the temperature on this day
	// void tempOnDay(int dateToCalculate) const; //Make a histogram of the temperature on this date
	// void tempPerDay() const; //Make a histogram of the average temperature of each day of the year
	// void hotCold() const; //Make a histogram of the hottest and coldest day of the year
	// void tempPerYear(int yearToExtrapolate) const; //Make a histogram of average temperature per year, then fit and extrapolate to the given year

	private:
	
};
#endif
