#include "CTimeSpan.h"

#include <iostream>
#include <sstream>


//  ==  Constructors  ==================================================================================================

CTimeSpan::CTimeSpan(const CTimeSpan &other) {
    days = other.days;
    hours = other.hours;
    minutes = other.minutes;
}


CTimeSpan::CTimeSpan(long double pointInTimeInDays) {
    days = (int) pointInTimeInDays;
    long double fractionalDays = pointInTimeInDays - days;

    long double hours_result = fractionalDays * HOURS_IN_A_DAY;
    hours = (int) hours_result;

    long double fractionalHours = hours_result - hours;
    long double minutes_result = fractionalHours * MINUTES_IN_AN_HOUR;
    minutes = (int) minutes_result;

    normalize();
}


CTimeSpan::CTimeSpan(int daysCount, int hoursCount, int minutesCount) {
    days = daysCount;
    hours = hoursCount;
    minutes = minutesCount;

    normalize();

    hours = hours % HOURS_IN_A_DAY;
    minutes = minutes % MINUTES_IN_AN_HOUR;
}


//  ==  Operators  =====================================================================================================

CTimeSpan CTimeSpan::operator+(const CTimeSpan &other) {
    int result_days = days + other.days;
    int result_hours = hours + other.hours;
    int result_minutes = minutes + other.minutes;

    normalize();

    return CTimeSpan(result_days, result_hours, result_minutes);
}


CTimeSpan CTimeSpan::operator-(const CTimeSpan &other) {
    int result_days = days - other.days;
    int result_hours = hours - other.hours;
    int result_minutes = minutes - other.minutes;

    normalize();

    return CTimeSpan(result_days, result_hours, result_minutes);
}


//  ==  Public methods  ================================================================================================

long double CTimeSpan::convertToYears() const {
    long double years = days / DAYS_IN_A_YEAR;
    years += hours / HOURS_IN_A_YEAR;
    years += minutes / MINUTES_IN_A_YEAR;

    return years;
}


std::string CTimeSpan::toString() {
    return "[" + convertToString(days) + " day(s), "
            + convertToString(hours) + " hour(s), "
            + convertToString(minutes) + " minute(s)]";
}


void CTimeSpan::printTimeSpan() {
    std::cout << toString() << "\n";
}


//  ==  Private methods  ===============================================================================================

std::string CTimeSpan::convertToString(int &num) const {
    std::stringstream ss;
    ss << num;

    return ss.str();
}


void CTimeSpan::normalize() {
    ifBelowZeroSetZero(days);

    adjustTime(minutes, hours, MINUTES_IN_AN_HOUR);
    adjustTime(hours, days, HOURS_IN_A_DAY);
}


void CTimeSpan::adjustTime(int &timeValue, int &toAdjust, const int &threshold) {
    if (timeValue >= threshold || timeValue < 0) {
        toAdjust += timeValue / threshold;
        timeValue %= threshold;

        if (timeValue < 0) {
            timeValue += threshold;
            toAdjust--;
        }
    }
}


void CTimeSpan::ifBelowZeroSetZero(int &value) {
    if (value < 0) value = 0;
}


//  ==  Getters and setters ============================================================================================

int CTimeSpan::getDaysCount() const {
    return days;
}

int CTimeSpan::getHoursCount() const {
    return hours;
}

int CTimeSpan::getMinutesCount() const {
    return minutes;
}

void CTimeSpan::setDaysCount(int daysCount) {
    ifBelowZeroSetZero(daysCount);

    days = daysCount;
}

void CTimeSpan::setHoursCount(int hoursCount) {
    ifBelowZeroSetZero(hoursCount);

    hours = hoursCount % HOURS_IN_A_DAY;
}

void CTimeSpan::setMinutesCount(int minutesCount) {
    ifBelowZeroSetZero(minutesCount);

    minutes = minutesCount % MINUTES_IN_AN_HOUR;
}
