#include <iostream>
#include "tempTrender.h"
#include "../include/tempTrender.h"
#include<fstream>

// ROOT stuff
#include<TH1.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TTimeStamp.h>
#include<TMath.h>

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
    filePath_m = filePath;
}

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

    TCanvas* c2 = new TCanvas("c2", "phi canvas", 900, 600);
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



void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const  //Make a histogram of the temperature on this day
{
    tempOnDay(TTimeStamp::GetDayOfYear(dayToCalculate, monthToCalculate, 2000));
}

void tempTrender::tempOnDay(int dateToCalculate) const  //Make a histogram of the temperature on this date
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


void tempTrender::covariance(std::string& file2Path){

    std::cout << "The second file path is "<< file2Path << "\n";
    
    //open files
    ifstream f1(filePath_m);
    ifstream f2(file2Path);

    //variables to load
    Int_t year;
    Int_t month;
    Int_t day;
    Int_t hour;
    Int_t min;
    Int_t sec;

    //variables for temperature
    Double_t temp1;
    Double_t temp2;

    //initiate the canvas
    TCanvas *c1 = new TCanvas("c1","Covariance Plot",900,600);
    //initiate the graph
    TGraph* plot = new TGraph();

    //load first lines
    f1 >> year >> month >> day >> hour >> min >> sec >> temp1;
    TTimeStamp t1(year, month, day, hour, min, sec);
    f2 >> year >> month >> day >> hour >> min >> sec >> temp2;
    TTimeStamp t2(year, month, day, hour, min, sec);
    
    Int_t idx=0;

    while (true){
        //std::cout << t1.AsString("s") << "\t" << t2.AsString("s") << "\n";
        if (t1 == t2){
            //add point to plot
            plot->SetPoint(idx++,temp1,temp2);
            //load next point
            if (f1.peek() == EOF || f2.peek() == EOF){
                break;
            }
            f1 >> year >> month >> day >> hour >> min >> sec >> temp1;
            t1.Set(year, month, day, hour, min, sec,0,kTRUE,0);
            f2 >> year >> month >> day >> hour >> min >> sec >> temp2;
            t2.Set(year, month, day, hour, min, sec,0,kTRUE,0);
        }else if (t1 < t2){
            //load next point
            if (f1.peek() == EOF){break;}
            f1 >> year >> month >> day >> hour >> min >> sec >> temp1;
            t1.Set(year, month, day, hour, min, sec,0,kTRUE,0);
        }else {
            //load next point
            if (f2.peek() == EOF){break;}
            f2 >> year >> month >> day >> hour >> min >> sec >> temp2;
            t2.Set(year, month, day, hour, min, sec,0,kTRUE,0);
        }
    }

    size_t start = filePath_m.find_last_of('/');
    size_t end = filePath_m.find_last_of('.');
    std::string city1 = filePath_m.substr(start+1,end-start-1);

    start = file2Path.find_last_of('/');
    end = file2Path.find_last_of('.');
    std::string city2 = file2Path.substr(start+1,end-start-1);

    plot->SetName("Covariance");
    plot->GetXaxis()->SetTitle(city1.c_str());
    plot->GetYaxis()->SetTitle(city2.c_str());
    plot->SetTitle("Covariance Plot");
    plot->Draw("A*");
}
