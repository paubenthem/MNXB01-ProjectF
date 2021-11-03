#ifndef COVTRENDER_H
#define COVTRENDER_H

class TimePoint{
    public:

        explicit TimePoint(int Y, int M, int D, int hr, int min);

        TimePoint operator+(int min);

    private:
        int year = 0;
        int month = 1;
        int day = 1;
        int hour = 0;
        int minuet = 0;

        int days_in_month(int month,int year);
};
#endif
