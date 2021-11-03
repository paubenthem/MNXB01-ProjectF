#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <sstream>
#include <fstream>

//root stuff
#include<TH1.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TTimeStamp.h>
#include<TMath.h>
#include<TGraph.h>


class tempTrender {
	public:
	explicit tempTrender(const std::string& filePath); //Construct using the specified file
	~tempTrender() {} //Destructor

	void tempOnDay(int monthToCalculate, int dayToCalculate) const; //Make a histogram of the temperature on this day
	void tempOnDay(int dateToCalculate) const; //Make a histogram of the temperature on this date
	void tempPerDay() const; //Make a histogram of the average temperature of each day of the year

    void covariance(std::string& file2Path);
    void covariance(std::string& file2Path,int minuet_timeLag);


	private:
        std::string filePath_m;
};
#endif
