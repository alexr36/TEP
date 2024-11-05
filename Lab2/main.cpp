#include <iostream>
#include "CNumber.h"

int main() {
    //  Test punktu 2.
    CNumber c_num_0, c_num_1, c_num_2, c_num_3, c_num_4, c_num_5;
    c_num_0 = 368;

    std::cout << c_num_0.sToStr() << std::endl;

    c_num_1 = 1567;
    c_num_0 = c_num_1;

    std::cout << c_num_0.sToStr() << std::endl;                 //  (1567)
    std::cout << c_num_1.sToStr() << std::endl;                 //  (1567)

    //  Dla liczby ujemnej
    c_num_2 = -42151331;
    std::cout << c_num_2.sToStr() << std::endl;                 //  (-42151331)

    c_num_3 = 123;
    c_num_4 = -123;
    c_num_5 = -1567;

    //  Testy dodawania
    std::cout << "\nTesty dodawania:" << std::endl;

    CNumber c_addition_test_1 = c_num_1 + c_num_3;              //  (1567 + 123 = 1690)
    std::cout << c_addition_test_1.sToStr() << std::endl;

    CNumber c_addition_test_2 = c_num_1 + 123;
    std::cout << c_addition_test_2.sToStr() << std::endl;       //  (1567 + 123 = 1690)

    CNumber c_addition_test_3 = c_num_1 + c_num_4;
    std::cout << c_addition_test_3.sToStr() << std::endl;       //  (1567 + (-123) = 1444)

    CNumber c_addition_test_4 = c_num_1 + (-123);
    std::cout << c_addition_test_4.sToStr() << std::endl;       //  (1567 + (-123) = 1444)

    CNumber c_addition_test_5 = c_num_4 + c_num_5;
    std::cout << c_addition_test_5.sToStr() << std::endl;       //  (-123 + (-1567) = -1690)

    //  Testy odejmowania
    std::cout << "\nTesty odejmowania:" << std::endl;

    CNumber c_subtraction_test_1 = c_num_1 - c_num_3;            //  (1567 - 123 = 1444)
    std::cout << c_subtraction_test_1.sToStr() << std::endl;

    CNumber c_subtraction_test_2 = c_num_1 - 123;
    std::cout << c_subtraction_test_2.sToStr() << std::endl;     //  (1567 - 123 = 1444)

    CNumber c_subtraction_test_3 = c_num_1 - c_num_4;            //  (1567 - (-123) = 1690)
    std::cout << c_subtraction_test_3.sToStr() << std::endl;

    CNumber c_subtraction_test_4 = c_num_1 - (-123);             //  (1567 - (-123) = 1690)
    std::cout << c_subtraction_test_4.sToStr() << std::endl;

    CNumber c_subtraction_test_5 = c_num_4 - c_num_5;
    std::cout << c_subtraction_test_5.sToStr() << std::endl;     //  (-123 - (-1567) = 1444)

    CNumber c_subtraction_test_6 = c_num_3 - c_num_1;            //  (123 - 1567 = (-1444))
    std::cout << c_subtraction_test_6.sToStr() << std::endl;

    CNumber c_subtraction_test_7 = c_num_3 - (1567);              // (123 - 1567 = (-1444))
    std::cout << c_subtraction_test_7.sToStr() << std::endl;

    //  Testy mnożenia
    std::cout << "\nTesty mnozenia:" << std::endl;

    CNumber c_num_6, c_num_7, c_num_8, c_num_9;

    c_num_6 = 15;
    c_num_7 = 20;
    c_num_8 = -15;
    c_num_9 = -20;

    CNumber c_multiplication_test_1 = c_num_6 * c_num_7;         //  (15 * 20 = 300)
    std::cout << c_multiplication_test_1.sToStr() << std::endl;

    CNumber c_multiplication_test_2 = c_num_6 * 20;             //  (15 * 20 = 300)
    std::cout << c_multiplication_test_2.sToStr() << std::endl;

    CNumber c_multiplication_test_3 = c_num_8 * c_num_9;        //  ((-15) * (-20) = 300)
    std::cout << c_multiplication_test_3.sToStr() << std::endl;

    CNumber c_multiplication_test_4 = c_num_6 * c_num_9;        //  (15 * (-20) = (-300))
    std::cout << c_multiplication_test_4.sToStr() << std::endl;

    CNumber c_multiplication_test_5 = c_num_8 * c_num_7;        //  ((-15) * 20 = (-300))
    std::cout << c_multiplication_test_5.sToStr() << std::endl;

    CNumber c_multiplication_test_6 = c_num_8 * (-20);          //  ((-15) * (-20) = 300)
    std::cout << c_multiplication_test_6.sToStr() << std::endl;

    CNumber c_multiplication_test_7 = c_num_8 * 0;              //  ((-15) * 0 = 0)
    std::cout << c_multiplication_test_7.sToStr() << std::endl;

    //  Testy dzielenia
    std::cout << "\nTesty dzielenia:" << std::endl;

    CNumber c_num_10, c_num_11, c_num_12, c_num_13, c_num_14, c_num_15;

    c_num_10 = 300;
    c_num_11 = 20;
    c_num_12 = 15;
    c_num_13 = -20;
    c_num_14 = -15;
    c_num_15 = -300;

    CNumber c_division_test_1 = c_num_10 / c_num_11;            //  (300 / 20 = 15)
    std::cout << c_division_test_1.sToStr() << std::endl;

    CNumber c_division_test_2 = c_num_10 / 20;                  //  (300 / 20 = 15)
    std::cout << c_division_test_2.sToStr() << std::endl;

    CNumber c_division_test_3 = c_num_10 / c_num_12;            //  (300 / 15 = 20)
    std::cout << c_division_test_3.sToStr() << std::endl;

    CNumber c_division_test_4 = c_num_10 / c_num_13;            //  (300 / (-20) = (-15))
    std::cout << c_division_test_4.sToStr() << std::endl;

    CNumber c_division_test_5 = c_num_10 / c_num_14;            // (300 / (-15) = (-20))
    std::cout << c_division_test_5.sToStr() << std::endl;

    CNumber c_division_test_6 = c_num_15 / c_num_11;            //  ((-300) / 20 = (-15))
    std::cout << c_division_test_6.sToStr() << std::endl;

    CNumber c_division_test_7 = c_num_11 / c_num_12;            //  (20 / 15 = 1)
    std::cout << c_division_test_7.sToStr() << std::endl;

    CNumber c_division_test_8 = c_num_12 / c_num_15;            //  (15 / 20 = 0)
    std::cout << c_division_test_8.sToStr() << std::endl;

    CNumber c_division_test_9 = c_num_15 / c_num_14;            //  ((-300) / (-15) = 20)
    std::cout << c_division_test_9.sToStr() << std::endl;

    CNumber c_division_test_10 = c_num_15 / 0;                  //  ((-300) / 0 = INT_MIN + error_message)
    std::cout << c_division_test_10.sToStr() << std::endl;

    //  Testy dla modulo
    std::cout << "\nTesty dla modulo:" << std::endl;

    CNumber c_num_16, c_num_17, c_num_18, c_num_19, c_num_20;

    c_num_16 = 5;
    c_num_17 = 4;
    c_num_18 = 3;
    c_num_19 = 2;
    c_num_20 = 1;

    CNumber c_modulo_test_1 = c_num_16 % c_num_17;              //  (5 % 4 = 1)
    std::cout << c_modulo_test_1.sToStr() << std::endl;

    CNumber c_modulo_test_2 = c_num_16 % c_num_18;              //  (5 % 3 = 2)
    std::cout << c_modulo_test_2.sToStr() << std::endl;

    CNumber c_modulo_test_3 = c_num_16 % c_num_19;              //  (5 % 2 = 1)
    std::cout << c_modulo_test_3.sToStr() << std::endl;

    CNumber c_modulo_test_4 = c_num_16 % c_num_20;              //  (5 % 1 = 0)
    std::cout << c_modulo_test_4.sToStr() << std::endl;

    CNumber c_modulo_test_5 = c_num_17 % c_num_19;              //  (4 % 2 = 0)
    std::cout << c_modulo_test_5.sToStr() << std::endl;

    CNumber c_modulo_test_6 = c_num_16 % 4;                     //  (5 % 4 = 1)
    std::cout << c_modulo_test_6.sToStr() << std::endl;

    CNumber c_modulo_test_7 = c_num_16 % 10;                    //  (5 % 10 = 5)
    std::cout << c_modulo_test_7.sToStr() << std::endl;

    CNumber c_modulo_test_8 = c_num_16 % 0;                     //  (5 % 0 = INT_MIN + error_message)
    std::cout << c_modulo_test_8.sToStr() << std::endl;

    //  Sprawdzenie poprawnosci operatorów:
    std::cout << "\nSprawdzenie poprawnosci dzialania operatorow:\n";
    CNumber c_test_379, c_test_999, c_test_m999, c_test_1000, c_test_22, c_test_m22, c_test_1, c_test_37, c_test_m11, c_test_m99, c_test_m2, c_test_121, c_test_3012, c_test_INT_MAX, c_test_364452, c_test_13, c_test_3448182, c_test_m123, c_test_m89998, c_test_m7777;
    c_test_379 = 379;
    c_test_999 = 999;
    c_test_m999 = -999;
    c_test_1000 = 1000;
    c_test_22 = 22;
    c_test_m22 = -22;
    c_test_1 = 1;
    c_test_37 = 37;
    c_test_m11 = -11;
    c_test_m99 = -99;
    c_test_m2 = -2;
    c_test_121 = 121;
    c_test_3012 = 3012;
    c_test_INT_MAX = INT_MAX;
    c_test_364452 = 364452;
    c_test_13 = 13;
    c_test_3448182 = 3448182;
    c_test_m123 = -123;
    c_test_m89998 = -89998;
    c_test_m7777 = -7777;

    std::cout << (c_test_379 - c_test_999).sToStr() << "\n";                //  (379 - 999 / (-620)
    std::cout << (c_test_379 + c_test_m999).sToStr() << "\n";               //  (379 + (-999) / (-620))
    std::cout << (c_test_1000 - c_test_22).sToStr() << "\n";                //  (1000 - 22 = 978)
    std::cout << (c_test_1000 + c_test_m22).sToStr() << "\n";               //  (1000 + (-22) = 978)
    std::cout << (c_test_999 + c_test_1).sToStr() << "\n";                  //  (999 + 1 = 1000)
    std::cout << (c_test_37 * c_test_m11).sToStr() << "\n";                 //  (37 * (-11) = (-407))
    std::cout << (c_test_m99 * c_test_m2).sToStr() << "\n";                 //  ((-99) * (-2) = 198)
    std::cout << (c_test_121 * c_test_3012).sToStr() << "\n";               //  (121 * 3012 = 364452)
    std::cout << (c_test_INT_MAX * c_test_INT_MAX).sToStr() << "\n";        //  (INT_MAX * INT_MAX = approx(4.6117 * 10^18))
    std::cout << (c_test_364452 / c_test_13).sToStr() << "\n";              //  (364452 / 13 = 28034)
    std::cout << (c_test_3448182 / c_test_m123).sToStr() << "\n";           //  (3448182 / (-123) = (-28034))
    std::cout << (c_test_m89998 / c_test_m7777).sToStr() << "\n";           //  ((-89998) / (-7777) = 11)

    //  Modyfikacja
    std::cout << "\nTesty dla modyfikacji:\n";

    CNumber c_num_21, c_num_22, c_num_23, c_num_24, c_num_25, c_num_26;
    c_num_21 = 33012;
    c_num_22 = 4124;
    c_num_23 = 1921;
    c_num_24 = 3471;
    c_num_25 = 9;
    c_num_26 = 333;

    CNumber c_mod_test_1 = c_num_21 ^ 3;                    //  (33012 ^ 3 = 012)
    std::cout << c_mod_test_1.sToStr() << "\n";

    CNumber c_mod_test_2 = c_num_22 ^ 4;                    //  (4124 ^ 4 = 4124)
    std::cout << c_mod_test_2.sToStr() << "\n";

    CNumber c_mod_test_3 = c_num_23 ^ 9;                    //  (1921 ^ 9 = 1921)
    std::cout << c_mod_test_3.sToStr() << "\n";

    CNumber c_mod_test_4 = c_num_24 ^ 10;                   //  (3471 ^ 10 = 3471)
    std::cout << c_mod_test_4.sToStr() << "\n";

    CNumber c_mod_test_5 = c_num_24 ^ -4;                   //  (3471 ^ (-4) = 3471)
    std::cout << c_mod_test_5.sToStr() << "\n";

    CNumber c_mod_test_6 = c_num_25 ^ 9;                    //  (9 ^ 9 = 0)
    std::cout << c_mod_test_6.sToStr() << "\n";

    CNumber c_mod_test_7 = c_num_26 ^ 3;                    //  (333 ^ 3 = 0)
    std::cout << c_mod_test_7.sToStr() << "\n";

    return 0;
}
