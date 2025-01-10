#ifndef CTIMESPAN_H
#define CTIMESPAN_H
#include <string>

#include "Constants.h"


class CTimeSpan {
    public:
        //  Constructors
        CTimeSpan(const CTimeSpan& other);
        CTimeSpan(long double pointInTimeInDays);
        CTimeSpan(int daysCount, int hoursCount, int minutesCount);

        //  Operators
        CTimeSpan operator+(const CTimeSpan& other);
        CTimeSpan operator-(const CTimeSpan& other);

        //  Public methods
        long double convertToYears() const;
        std::string toString();
        void printTimeSpan();

        //  Getters
        int getDaysCount() const;
        int getHoursCount() const;
        int getMinutesCount() const;

        //  Setters
        void setDaysCount(int daysCount);
        void setHoursCount(int hoursCount);
        void setMinutesCount(int minutesCount);

    private:
        //  Class fields
        int days;
        int hours;
        int minutes;

        //  Aux methods
        std::string convertToString(int &num) const;
        void normalize();
        void adjustTime(int &timeValue, int &toAdjust, const int &threshold);
        void ifBelowZeroSetZero(int &value);
};


#endif //CTIMESPAN_H
