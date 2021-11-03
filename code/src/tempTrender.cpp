#include <iostream>
#include "tempTrender.h"

#include<fstream>

// ROOT stuff
#include<TH1.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TTimeStamp.h>
#include<TMath.h>

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
	
	/*Int_t i = 0;
	while (file >> year >> month >> day >> h >> min >> sec >> temp) {
		Y[i] = year;
		M[i] = month;
		D[i] = day;
		H[i] = h;
		MN[i] = min;
		S[i] = sec;
		i++;
	}*/
}

// void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const {} //Make a histogram of the temperature on this day
// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
void tempTrender::tempPerDay() const {
Int_t year;
Int_t month;
Int_t day;
Int_t h;
Int_t min;
Int_t sec;
Int_t prev_day;
Int_t prev_month;
Int_t prev_year;
Double_t temp;
Double_t day_temp_sum;
Double_t day_mean;
Int_t same_day_num;
Int_t bin_num;


TH1D* hTemp = new TH1D("hTemp", "Mean temperature change throughout the year; Day of the year; Mean temperature", 
			366, 1, 367);
ifstream file("/home/an2228pas/Proj/MNXB01-ProjectF/code/src/Falsterbo.csv");

TTimeStamp prev_stamp(0, 0, 0, 0, 0, 0, 0);
Int_t first = 1;
Double_t normalization[366]; 
for (Int_t i = 0; i<366; i++) normalization[i]=0;
Int_t count = 0;
while (file >> year >> month >> day >> h >> min >> sec >> temp) {
count++;
TTimeStamp stamp(year, month, day, h, min, sec);


if (stamp == prev_stamp) {              // add temperature over the day and count entries 
	day_temp_sum += temp;
	same_day_num++;
}
else {
	if (first != 1) {           // add to histogram if not looping over first line
		day_mean = day_temp_sum/same_day_num;
		bin_num = prev_stamp.GetDayOfYear();  
		//cout << "Day number: " << bin_num << endl;
		hTemp->Fill(bin_num, day_mean); // add to histogram into correct bin
		normalization[bin_num-1] = normalization[bin_num-1] + 1; 
		//cout << "Bin: " << bin_num << ". Normalization: " << normalization[bin_num-1] << endl;
	}

	prev_stamp = stamp;
	same_day_num = 1;
	day_temp_sum = temp;
}
first = 0;

}
//cout << "loop ran for " << count << endl;

TCanvas* c1 = new TCanvas("c1", "phi canvas", 900, 600);
Double_t mean_value;
for (Int_t i = 1; i < 367; i++) {
mean_value = (hTemp->GetBinContent(i))/normalization[i-1];
//cout << "Bin: " << i << ". Normalization: " << normalization[i-1]<< ". Value: "<< mean_value << endl;
hTemp->SetBinContent(i, mean_value);
hTemp->SetBinError(i, TMath::Sqrt(TMath::Abs(mean_value)));
}

//hTemp->SetMinimum(-400);
hTemp->Draw();	
} 
//Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
