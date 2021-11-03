#include "TimePoint.h"

TimePoint::TimePoint(int Y, int M, int D, int hr, int min){
    hr += min/60;
    D += hr/24;
    Y += (M-1)/12;
    M = (M%12)+1;
    while (D>days_in_month(M,Y)){
        D -= days_in_month(M++,Y);
        if (M>12){
            M=1;
            Y++;
        }
    }


    minuet = min % 60;
    hour = hr %24;
    day = D;
    month = M;
    year = Y;
    
}


TimePoint::TimePoint operator+(int min){
    return TimePoint(getYear(),getMonth(),getDay(),getHour(),getMinuet()+min);

}

int TimePoint::days_in_month(int month, int year){
    if (month == 2){
        if (year % 4 == 0){
            if(year % 100 == 0){
                if (year % 400 == 0){
                    return 29;
                }
                return 28;
            }
            return 29;
        }
        return 28;
    }
    else if (month <= 7){
        return 30 + (month%2);
    } else {
        return 31 - (month%2);
    }
}
