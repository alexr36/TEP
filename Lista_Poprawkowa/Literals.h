#ifndef LITERALS_H
#define LITERALS_H
#include "Constants.h"
#include "CTimeSpan.h"


CTimeSpan operator""_d(unsigned long long timespanInDays) {
    return CTimeSpan(timespanInDays, 0, 0);
}


CTimeSpan operator""_h(unsigned long long timespanInHours) {
    int days = timespanInHours / HOURS_IN_A_DAY;
    timespanInHours -= days * HOURS_IN_A_DAY;

    return CTimeSpan(days, timespanInHours, 0);
}


CTimeSpan operator""_m(unsigned long long timespanInMinutes) {
    int hours = timespanInMinutes / MINUTES_IN_AN_HOUR;
    timespanInMinutes -= hours * MINUTES_IN_AN_HOUR;

    int days = hours / HOURS_IN_A_DAY;
    hours -= days * HOURS_IN_A_DAY;

    return CTimeSpan(days, hours, timespanInMinutes);
}

#endif //LITERALS_H
