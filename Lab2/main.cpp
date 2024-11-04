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

    return 0;
}

