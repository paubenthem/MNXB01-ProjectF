#include "tempTrender.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TDatime.h>

// function that checks whether a string is a number
bool isInt(std::string& str) {
	for (auto &ch: str) {
			if (!std::isdigit(ch)) return false; 
	}
	return true;
}

void project(std::string datapath) {
	
	

	std::cout << "Path " << datapath << " specified." << std::endl;

	tempTrender t(datapath);

	size_t start = datapath.find_last_of('/');
    size_t end = datapath.find_last_of('.');
    std::string city1 = datapath.substr(start+1,end-start-1);

	std::cout << "Would you like to see the covariance between " << city1 << " and another city? (y/n)"  << std::endl;
	std::string ans1;
	std::cin >> ans1;
	
	while (ans1 != "y" && ans1 != "n") {
		std::cout << "Invalid input. Please enter \"y\" or \"n\": ";
		std::cin >> ans1;
	}
	std::string datapath2;
	std::string offset;
	if (ans1 == "y") {
		std::cout << "Enter datapath for the second city:" << std::endl;
		std::cin >> datapath2;
		std::ifstream file2(datapath2);
		bool works = file2.is_open();
		while (!works) {
			std::cout << "Invalid path or file does not exist. Please enter a valid path:" << std::endl;
			std::cin >> datapath2;
			std::ifstream file2(datapath2);
			works = file2.is_open();
		}
		start = datapath2.find_last_of('/');
		end = datapath2.find_last_of('.');
	    std::string city2 = datapath2.substr(start+1,end-start-1);
		std::cout << "Enter the offset in minutes between " << city1 << " and " << city2 << ": ";
		std::cin >> offset;
		while (!isInt(offset)) {
			std::cout << "Offset must be an integer. Enter offset: ";
			std::cin >> offset;
		} 
			
	} 
	
	std::cout << "For temperature on a given day, would you like to enter month and day or number of day in the year? (md/n):" << std::endl;
	std::string ans2;
	std::cin >> ans2;
	while (ans2 != "md" && ans2!= "n") {
		std::cout << "Invalid input. Please enter \"md\" or \"n\": ";
		std:cin >> ans2;
	}
	if (ans2 == "md") {
		std::cout << "Enter month and day: ";
		Int_t m,d;	
		std::cin >> m >> d;
		Int_t date;
		date = 2000*10000 + m*100 + d;
		while (TDatime::GetLegalGlobalDayFromDate(date) == 0) {
			std::cout << "Invalid date entered. Please enter a valid month and day pair: ";
			std::cin >> m >> d;
			date = 2000*10000 + m*100 + d;
		}		
		t.tempOnDay(m,d);
	} else if (ans2 == "n") {
		std::cout << "Enter number of day in the year: ";
		Int_t n;	
		std::cin >> n;
		while (n>366 || n<1) {
			std::cout << "Invalid day in the year. Please enter a number between 1 and 366: ";
			std::cin >> n;
		}
		t.tempOnDay(n);
	}	
	
	
	t.tempPerDay();
	
	if (ans1 == "y") {
		stringstream offset_int_obj(offset);
		int offset_int;
		offset_int_obj >> offset_int;
		t.covariance(datapath2, offset_int);
	}	

}



