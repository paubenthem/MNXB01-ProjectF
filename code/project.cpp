#include "tempTrender.h"
#include <string>

void project() {
	const std::string pathToFile = "src/Falsterbo.csv"; //Put the path to your data file here


	tempTrender t(pathToFile); //Instantiate your analysis object
	
	t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
    t.tempPerDay();
}
