#ifndef CDATETIME_H
#define CDATETIME_H
#include "CTimeSpan.h"


class CDateTime {
    public:
        //  Constructors
        CDateTime(long double pointInTimeInDays);
        CDateTime(int year, int month, int day, int hour, int minute);
        CDateTime(const CDateTime &other);

        //  Operators
        bool operator<(const CDateTime &other) const;
        bool operator<=(const CDateTime &other) const;
        bool operator>(const CDateTime &other) const;
        bool operator>=(const CDateTime &other) const;
        bool operator==(const CDateTime &other) const;
        bool operator!=(const CDateTime &other) const;

        CDateTime operator+(const CTimeSpan &timeSpan) const;
        CDateTime operator-(const CTimeSpan &timeSpan) const;

        CTimeSpan operator-(const CDateTime &other) const;

        //  Public methods
        std::string toString();
        void printDateTime();

        //  Getters and setters
        long double getPointInTime() const;
        void setPointInTime(long double);

    private:
        //  Class fields
        long double point_in_time_in_years;

        //  Aux methods
        bool isLeapYear(int &year);
        long double convertToYears(int &year, int &month, int &day, int &hour, int &minute);
        std::string convertToString(long double &num) const;

};


#endif //CDATETIME_H
