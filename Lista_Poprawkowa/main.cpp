#include <iostream>

#include "CDateTime.h"
#include "CTimeSpan.h"
#include "Literals.h"

void timeSpanTests() {
    std::cout << "Testing CTimeSpan:\n";

    CTimeSpan ts_1 = CTimeSpan(4, 26, 71);
    ts_1.printTimeSpan();

    CTimeSpan ts_2 = CTimeSpan(15, 7, 31);
    ts_2.printTimeSpan();

    CTimeSpan ts_3 = ts_1 + ts_2;
    std::cout << ts_1.toString() << " + " << ts_2.toString() << " = " << ts_3.toString() << "\n";

    CTimeSpan ts_4 = ts_2 - ts_1;
    std::cout << ts_2.toString() << " - " << ts_1.toString() << " = " << ts_4.toString() << "\n";

    CTimeSpan ts_5 = ts_1 - ts_2;
    std::cout << ts_1.toString() << " - " << ts_2.toString() << " = " << ts_5.toString() << "\n";

    CTimeSpan ts_6 = ts_3 - ts_4;
    std::cout << ts_3.toString() << " - " << ts_4.toString() << " = " << ts_6.toString() << "\n";

    CTimeSpan ts_7 = ts_6 - ts_3;
    std::cout << ts_6.toString() << " - " << ts_3.toString() << " = " << ts_7.toString() << "\n";

    CTimeSpan ts_8 = ts_7 - ts_3;
    std::cout << ts_7.toString() << " - " << ts_3.toString() << " = " << ts_8.toString() << "\n";

    CTimeSpan ts_9 = CTimeSpan(4, 5, 2) - CTimeSpan(2, 7, 3);
    ts_9.printTimeSpan();

    CTimeSpan ts_10 = 12_d + 5_h + 30_m;
    ts_10.printTimeSpan();

    CTimeSpan ts_11 = 12_d - 5_h - 30_m;
    ts_11.printTimeSpan();

    CTimeSpan ts_12 = 0_d + 5_h - 30_m;
    ts_12.printTimeSpan();

    CTimeSpan(-4, 5, 21).printTimeSpan();

    std::cout << "\n";
}


void dateTimeTests() {
    std::cout << "Testing CDateTime:\n";

    CDateTime dt_1(2024, 1, 15, 12, 0);
    CDateTime dt_2(2023, 12, 31, 23, 59);
    CDateTime dt_3(2024, 1, 1, 0, 0);
    CDateTime dt_4(dt_1);

    CTimeSpan ts_1 = 1_d + 5_h + 30_m;
    CTimeSpan ts_2 = 2_d + 2_h;

    std::cout << dt_1.toString() << " > " << dt_2.toString() << ": " << (dt_1 > dt_2) << "\n";
    std::cout << dt_1.toString() << " < " << dt_2.toString() << ": " << (dt_1 < dt_2) << "\n";
    std::cout << dt_1.toString() << " == " << dt_2.toString() << ": " << (dt_1 == dt_2) << "\n";
    std::cout << dt_1.toString() << " == " << dt_4.toString() << ": " << (dt_1 == dt_4) << "\n";
    std::cout << dt_1.toString() << " >= " << dt_2.toString() << ": " << (dt_1 >= dt_2) << "\n";
    std::cout << dt_1.toString() << " >= " << dt_4.toString() << ": " << (dt_1 >= dt_4) << "\n";
    std::cout << dt_1.toString() << " != " << dt_2.toString() << ": " << (dt_1 != dt_2) << "\n";

    CDateTime result1 = dt_1 + ts_1;
    std::cout << dt_1.toString() << " + " << ts_1.toString() << " = " <<result1.toString() << "\n";

    CDateTime result2 = dt_1 - ts_2;
    std::cout << dt_1.toString() << " - " << ts_2.toString() << " = " << result2.toString() << "\n";

    CTimeSpan diff = dt_1 - dt_3;
    std::cout << dt_1.toString() << " - " << dt_3.toString() << " = " << diff.toString() << "\n";
}


void test() {
    timeSpanTests();
    dateTimeTests();
}

int main() {
    test();

    return 0;
}