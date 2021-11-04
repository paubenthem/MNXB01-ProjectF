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
	// Initialization of variables	
	Int_t year = 0;
    Int_t month = 0;
    Int_t day = 0;
    Int_t h = 0;
    Int_t min = 0;
    Int_t sec = 0;
    Double_t temp = 0;
    Double_t day_temp_sum = 0;
    Double_t day_mean = 0;
    Int_t same_day_num = 0;
    Int_t bin_num = 0;
	
	// Histogram creation. 366 days in leap year. 		 
    TH1D* hTemp = new TH1D("hTemp", "Mean temperature change throughout the year; Day of the year; Mean temperature [#circC]", 
                366, 1, 367);
    ifstream file(filePath_m); // Open file 

    bool first = true; // variable used to check whether the while loop is on first iteration
    Double_t normalization[366]; // array for normalizing bins, counts # of times bin was filled
    for (Int_t i = 0; i<366; i++) normalization[i]=0; // setting array to 0's

    TTimeStamp prev_stamp(0, 0, 0, 0, 0, 0, 0);
	// Main loop of the file, runs until the last line of the file
    while (file >> year >> month >> day >> h >> min >> sec >> temp) {
		TTimeStamp stamp(year, month, day, h, min, sec);

		if (stamp == prev_stamp) {          // logic for the same date     
		    day_temp_sum += temp;			// add temperature over the day and count entries
		    same_day_num++;
		}
		else {
		    if (!first) {           // add to histogram if not looping over first line
		        day_mean = day_temp_sum/same_day_num;
		        bin_num = prev_stamp.GetDayOfYear();  

		        hTemp->Fill(bin_num, day_mean); // add to histogram into correct bin
		        normalization[bin_num-1] = normalization[bin_num-1] + 1; 
		    }
		    prev_stamp = stamp;
		    same_day_num = 1;
		    day_temp_sum = temp;
		}
		first = false;

	}
	// adds the last group of dates to the histogram
	day_mean = day_temp_sum/same_day_num;
	bin_num = prev_stamp.GetDayOfYear();
	hTemp->Fill(bin_num, day_mean);
	normalization[bin_num-1] += 1;

	TCanvas* c2 = new TCanvas("c2", "Mean temperature over the year", 900, 600);
	
	// Normalization of temperature and associated errors	
	Double_t mean_value;
	for (Int_t i = 1; i < 367; i++) {
	    mean_value = (hTemp->GetBinContent(i))/normalization[i-1];
	    hTemp->SetBinContent(i, mean_value);
	    hTemp->SetBinError(i, TMath::Sqrt(TMath::Abs(mean_value)));
    }
	Double_t maximum, minimum;
	maximum = hTemp->GetMaximum();
	minimum = hTemp->GetMinimum();
	std::cout << "For the average temperature throughout the year:" << std::endl; 
	std::cout << "Max: " << maximum << ", Min: " << minimum << std::endl;
    
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
	
	// Calculate number of entries: (can be used to calculate probability of a specific temperature on given day)
	int entries = hist->GetEffectiveEntries();

	cout << " The mean temperature of the day " << dateToCalculate << " is " << mean << "\n" << endl;
	cout << " The standard deviation of the temperature is " << stdev << "\n" << endl;
	cout << " The number of entries in the histogram is " << entries << "\n" << endl;

	// Create a new canvas and draw the histogram
	TCanvas* can = new TCanvas("can", "The temperature of a given day", 900, 600);
	
	hist->Draw();

}


void tempTrender::covariance(std::string& file2Path){
    covariance(file2Path, 0);
}

void tempTrender::covariance(std::string& file2Path, int minuet_timeLag){

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
    TTimeStamp t2(year, month, day, hour, min+minuet_timeLag, sec);
    
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
            t2.Set(year, month, day, hour, min + minuet_timeLag, sec,0,kTRUE,0);
        }else if (t1 < t2){
            //load next point
            if (f1.peek() == EOF){break;}
            f1 >> year >> month >> day >> hour >> min >> sec >> temp1;
            t1.Set(year, month, day, hour, min, sec,0,kTRUE,0);
        }else {
            //load next point
            if (f2.peek() == EOF){break;}
            f2 >> year >> month >> day >> hour >> min >> sec >> temp2;
            t2.Set(year, month, day, hour, min + minuet_timeLag, sec,0,kTRUE,0);
        }
    }

    std::cout << "number of points plotted:" << idx <<"\n";

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
