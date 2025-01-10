#ifndef LITERALS_H
#define LITERALS_H
#include "Constants.h"
#include "CTimeSpan.h"


CTimeSpan operator""_d(unsigned long long timespan_in_days) {
    return CTimeSpan(timespan_in_days, 0, 0);
}


CTimeSpan operator""_h(unsigned long long timespan_in_hours) {
    int days = timespan_in_hours / HOURS_IN_A_DAY;
    timespan_in_hours -= days * HOURS_IN_A_DAY;

    return CTimeSpan(days, timespan_in_hours, 0);
}


CTimeSpan operator""_m(unsigned long long timespan_in_minutes) {
    int hours = timespan_in_minutes / MINUTES_IN_AN_HOUR;
    timespan_in_minutes -= hours * MINUTES_IN_AN_HOUR;

    int days = hours / HOURS_IN_A_DAY;
    hours -= days * HOURS_IN_A_DAY;

    return CTimeSpan(days, hours, timespan_in_minutes);
}

#endif //LITERALS_H
