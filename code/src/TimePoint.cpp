#include "TimePoint"

int TimePoint::days_in_month(int month, int year){
    if (month == 2){
        if (year % 4 == 0){
            if(year % 100 == 0){
                if (year % 400 = 0){
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
