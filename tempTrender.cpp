#include <iostream>
#include "tempTrender.h"

#include <fstream> 

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h>

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
	filePath_m=filePath;
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const //Make a histogram of the temperature on this day
{

	Int_t year;
	Int_t month;
	Int_t day;
	Int_t h;
	Int_t min;
	Int_t sec;
	Double_t temp;

	// open input file
	ifstream file(filePath_m);

	// Create histogram	for the temperature of a given day
	TH1I* hist = new TH1I("temperature", "Temperature; Temperature [#circC]; Entries", 
				300, -20, 40);

	// Set the Fill color to a darker red
	hist-> SetFillColor(kRed+1);

	// loop over data 
	while (file >> year >> month >> day >> h >> min >> sec >> temp) {
		if (month == monthToCalculate)  {              
			if (day == dayToCalculate) {
				hist -> Fill(temp); // Fill histogram with temperature from that day over all years.
			}
		}
	}

	// Calculate the mean temperatura of the given day
	double mean = hist->GetMean();	
	// Calculate the standard deviation of the temperature
	double stdev = hist->GetRMS();	
	
//	cout << " The mean temperature of the day " << monthToCalculate << " " << dayToCalculate << " is " << mean << "\n" << endl;
//	cout << " The standard deviation of the temperature is " << stdev << "\n" << endl;
	
	// Create a new canvas and draw the histogram
	TCanvas* can = new TCanvas("can", "The temperature of a given day", 900, 600);
	
	hist->Draw();

} 

void tempTrender::tempOnDay(int dateToCalculate) const //Make a histogram of the temperature on this date
{

	Int_t year;
	Int_t month;
	Int_t day;
	Int_t h;
	Int_t min;
	Int_t sec;
	Double_t temp;

	// open input file
	ifstream file(filePath_m);

	// Create histogram	for the temperature of a given day
	TH1I* hist = new TH1I("temperature", "Temperature; Temperature [#circC]; Entries", 
				300, -20, 40);

	// Set the Fill color to a darker red
	hist-> SetFillColor(kRed+1);

	// loop over data 
	while (file >> year >> month >> day >> h >> min >> sec >> temp) {
		if (TTimeStamp::GetDayOfYear(day, month, year) == dateToCalculate)  {              
				hist -> Fill(temp); // Fill histogram with temperature from that day over all years.
		}
	}

	// Calculate the mean temperatura of the given day
	double mean = hist->GetMean();	
	// Calculate the standard deviation of the temperature
	double stdev = hist->GetRMS();	
	
//	cout << " The mean temperature of the day " << monthToCalculate << dayToCalculate << " is " << mean << "\n" << endl;
//	cout << " The standard deviation of the temperature is " << stdev << "\n" << endl;
	
	// Create a new canvas and draw the histogram
	TCanvas* can = new TCanvas("can", "The temperature of a given day", 900, 600);
	
	hist->Draw();

}

// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year

