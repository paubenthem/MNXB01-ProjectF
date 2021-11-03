#include <iostream>
#include "../include/tempTrender.h"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
    filePath_m = filePath;
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const  //Make a histogram of the temperature on this day
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
	
	cout << " The mean temperature of the day " << monthToCalculate << dayToCalculate << " is " << mean << "\n" << endl;
	cout << " The standard deviation of the temperature is " << stdev << "\n" << endl;
	
	// Create a new canvas and draw the histogram
	TCanvas* can = new TCanvas("can", "The temperature of a given day", 900, 600);
	
	hist->Draw();
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

    //initiate the graph
    TGraph* plot = new TGraph();

    //load first lines
    f1 >> year >> month >> day >> hour >> min >> sec >> temp1;
    TTimeStamp t1(year, month, day, hour, min, sec);
    f2 >> year >> month >> day >> hour >> min >> sec >> temp2;
    TTimeStamp t2(year, month, day, hour, min, sec);
    
    while (true){
        //std::cout << t1.AsString("s") << "\t" << t2.AsString("s") << "\n";
        if (t1 == t2){
            //add point to plot
       //     plot->AddPoint(temp1,temp2);
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
    plot->GetXaxis()->SetTitle("This city");
    plot->GetYaxis()->SetTitle("Other city");
    plot->SetTitle("Covariance Plot");
    plot->Draw("A*");
}
