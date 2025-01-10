#include "CDateTime.h"

#include <iostream>
#include <sstream>

#include "Constants.h"

//  ==  Constructors  ==================================================================================================

CDateTime::CDateTime(long double pointInTimeInYears) {
    point_in_time_in_years = pointInTimeInYears;
}


CDateTime::CDateTime(int year, int month, int day, int hour, int minute) {
    point_in_time_in_years = convertToYears(year, month, day, hour, minute);
}


CDateTime::CDateTime(const CDateTime &other) {
    point_in_time_in_years = other.point_in_time_in_years;
}


//  ==  Operators  =====================================================================================================

bool CDateTime::operator<(const CDateTime &other) const {
    return point_in_time_in_years < other.point_in_time_in_years;
}

bool CDateTime::operator<=(const CDateTime &other) const {
    return point_in_time_in_years <= other.point_in_time_in_years;
}

bool CDateTime::operator>(const CDateTime &other) const {
    return point_in_time_in_years > other.point_in_time_in_years;
}

bool CDateTime::operator>=(const CDateTime &other) const {
    return point_in_time_in_years >= other.point_in_time_in_years;
}

bool CDateTime::operator==(const CDateTime &other) const {
    return point_in_time_in_years == other.point_in_time_in_years;
}

bool CDateTime::operator!=(const CDateTime &other) const {
    return point_in_time_in_years != other.point_in_time_in_years;
}


CDateTime CDateTime::operator+(const CTimeSpan &timeSpan) const {
    long double timespan_in_days = timeSpan.convertToYears();

    return CDateTime(point_in_time_in_years + timespan_in_days);
}

CDateTime CDateTime::operator-(const CTimeSpan &timeSpan) const {
    long double timespan_in_days = timeSpan.convertToYears();

    return CDateTime(point_in_time_in_years - timespan_in_days);
}


CTimeSpan CDateTime::operator-(const CDateTime &other) const {
    long double result = point_in_time_in_years - other.point_in_time_in_years;

    return CTimeSpan(result);
}


//  ==  Public methods  ================================================================================================

std::string CDateTime::toString() {
    return convertToString(point_in_time_in_years);
}


void CDateTime::printDateTime() {
    std::cout << point_in_time_in_years << std::endl;
}


//  ==  Private methods  ===============================================================================================

//  According to the Gregorian calendar
bool CDateTime::isLeapYear(int &year) {
    return (year % LEAP_YEAR_INDICATOR_4 == 0
            && year % LEAP_YEAR_INDICATOR_100 != 0)
            || year % LEAP_YEAR_INDICATOR_400 == 0;
}


long double CDateTime::convertToYears(int &year, int &month, int &day, int &hour, int &minute) {
    long double years = year;
    years += (long double) (month - 1) * DAYS_IN_MONTH_AVG / DAYS_IN_A_YEAR;
    years += (long double) (day - 1) / DAYS_IN_A_YEAR;
    years += (long double) hour / HOURS_IN_A_YEAR;
    years += (long double) minute / MINUTES_IN_A_YEAR;

    return years;
}


std::string CDateTime::convertToString(long double &num) const {
    std::stringstream ss;
    ss << num;

    return ss.str();
}


//  ==  Getters and setters ============================================================================================

long double CDateTime::getPointInTime() const {
    return point_in_time_in_years;
}

void CDateTime::setPointInTime(long double new_point_in_time) {
    point_in_time_in_years = new_point_in_time;
}

