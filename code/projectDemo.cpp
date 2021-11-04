#include <string>
#include "tempTrender.h"

void projectDemo(){
    std::string cityDataPath = "../data_clean/Lund.csv";
    tempTrender city1(cityDataPath);

    city1.tempOnDay(03,02);
    city1.tempPerDay();

    std::string cityDataPath2 = "../data_clean/Falsterbo.csv";
    city1.covariance(cityDataPath2);
}
