#include <iostream>
#include "../include/tempTrender.h"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
    filePath_m = filePath;
}

// void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const {} //Make a histogram of the temperature on this day
// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
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
    std::string c1 = filePath_m.substr(start+1,end-start-1);

    start = file2Path.find_last_of('/');
    end = file2Path.find_last_of('.');
    std::string c2 = file2Path.substr(start+1,end-start-1);

    plot->SetName("Covariance");
    plot->GetXaxis()->SetTitle(c1.c_str());
    plot->GetYaxis()->SetTitle(c2.c_str());
    plot->SetTitle("Covariance Plot");
    plot->Draw("A*");
}
