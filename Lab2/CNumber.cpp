#include "CNumber.h"
#include <iostream>
#include "constants.h"
#include <sstream>

//  Konstruktor domyślny
CNumber::CNumber() {
    i_length = NUMBER_DEFAULT_LENGTH;
    pi_number = new int[i_length];
    b_is_negative = false;
}

//  Destruktor
CNumber::~CNumber() {}

//  --  Gettery i settery ----------------------------------------------------------------------------------------------

void CNumber::vSetLength(int iNewLength) {
    if (iNewLength >= 0) i_length = iNewLength;
    else std::cout << "CNumber::vSetLength: Invalid length " << iNewLength << std::endl;
}

void CNumber::vSetIsNegative(bool bIsNegative) {
    b_is_negative = bIsNegative;
}

void CNumber::vSetNumber(int* piNewNumber) {
    delete[] pi_number;
    pi_number = piNewNumber;
}

int CNumber::iGetLength() {
    return i_length;
}

bool CNumber::bIsNegative() {
    return b_is_negative;
}

int* CNumber::piGetNumber() {
    return pi_number;
}

//  --  Operatory ------------------------------------------------------------------------------------------------------

//  --  Operatory dla obiektów klasy    --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

//  Operator przypisania
void CNumber::operator=(const CNumber &pcNewVal) {
    if (this == &pcNewVal) return;                   //  Zabezpieczenie przed samoprzydzielaniem

    delete[] pi_number;                             //  Dealokacja nieużywanego obszaru pamięci

    i_length = pcNewVal.i_length;                    //  Przypisanie odpowiedniej długości liczby
    b_is_negative = pcNewVal.b_is_negative;          //  Oznaczenie znaku liczby

    //  Kopiowanie cyfr i alokacja potrzebnej pamięci
    pi_number = new int[i_length];
    for (int i = 0; i < i_length; i++) {
        pi_number[i] = pcNewVal.pi_number[i];
    }
}

//  Operator dodawania
CNumber CNumber::operator+(const CNumber &pcNewVal) {
    CNumber c_result;

    //  Wykonanie operacji dodawania, jeśli znaki obydwu składników są takie same
    if (b_is_negative == pcNewVal.b_is_negative) {
        int i_max_length = std::max(i_length, pcNewVal.i_length);        //  Obliczenie maksymalnej długości liczby
        c_result.i_length = i_max_length + 1;                               //  Dostosowanie długości liczby wynikowej

        delete[] c_result.pi_number;
        c_result.pi_number = new int[i_max_length];

        int i_carry = 0;                                                    //  Potencjalne przeniesienie

        //  Pętla wykonuje się tak długo, aż wszystkie cyfry zostaną przetworzone i przeniesienie jest równe zero
        for (int i = 0; i < i_max_length || i_carry > 0; i++) {

            //  Wzięcie kolejnej cyfry pierwszego składnika (od końca)
            int i_digit_1 = (i < i_length) ? pi_number[i_length - i - 1] : 0;

            //  Wzięcie kolejnej cyfry drugiego składnika (od końca)
            int i_digit_2 = (i < pcNewVal.i_length) ? pcNewVal.pi_number[pcNewVal.i_length - i - 1] : 0;

            //  Obliczenie sumy - wynikowej cyfry z uwzględnieniem przeniesienia
            int i_sum = i_digit_1 + i_digit_2 + i_carry;

            //  Pozbycie się nadmiaru (jeśli wartość i_sum wykracza poza 0-9)
            c_result.pi_number[c_result.i_length - i - 1] = i_sum % NUMERIC_SYSTEM_BASE;
            i_carry = i_sum / NUMERIC_SYSTEM_BASE;                          //  Obliczenie wartości przeniesienia

        }

        c_result.removeLeadingZeros();                                      //  Usunięcie zer wiodących, jeśli są
        c_result.b_is_negative = b_is_negative;                             //  Ustawienie znaku wyniku
    }
    //  Jeśli znaki składników są przeciwne, należy przeprowadzić odejmowanie
    else {
        if (b_is_negative) {
            CNumber c_temp = *this;
            c_result.b_is_negative = false;
            c_result = c_temp - *this;
        }
        else {
            CNumber c_temp = pcNewVal;
            c_temp.b_is_negative = false;
            c_result = *this - c_temp;
        }
    }

    normalizeZeroSign(c_result);                                         // Jeśli wynik jest równy zero to ustawiamy jego znak na dodatni
    return c_result;                                                        //  Zwrócenie wyniku
}

//  Operator odejmowania
CNumber CNumber::operator-(const CNumber &pcNewVal) {
    CNumber pcOtherCopy = pcNewVal;
    CNumber c_result;

    //  Jeśli liczby mają różne znaki, zamiast odejmowania należy wykonać dodawanie
    if (b_is_negative != pcNewVal.b_is_negative) {
        CNumber c_temp = pcNewVal;
        c_temp.b_is_negative = !pcNewVal.b_is_negative;

        return *this + c_temp;
    }

    //  Sprawdzenie, która z liczb jest mniejsza
    bool b_this_is_smaller = false;

    if (i_length < pcNewVal.i_length) b_this_is_smaller = true;
    else if (i_length == pcNewVal.i_length) b_this_is_smaller = !bIsGreater(*this, pcOtherCopy);

    const CNumber* pc_larger;
    const CNumber* pc_smaller;

    //  Ustalanie, która z liczb jest większa
    if (b_this_is_smaller) {
        pc_smaller = this;
        pc_larger = &pcNewVal;

        //  Jeśli od mniejszej liczby odejmujemy większą, wynik będzie ujemny
        c_result.b_is_negative = !b_is_negative;
    }
    else {
        pc_smaller = &pcNewVal;
        pc_larger = this;

        //  Jeśli od większej liczby odejmujemy mniejszą, wynik będzie dodatni
        c_result.b_is_negative = b_is_negative;
    }

    c_result.i_length = pc_larger->i_length;
    delete[] c_result.pi_number;
    c_result.pi_number = new int[c_result.i_length];

    int i_borrow = 0;                                           //  Potencjalna pożyczka

    for (int i = 0; i < c_result.i_length; i++) {
        //  Wzięcie kolejnej cyfry pierwszej liczby (od końca)
        int i_digit_1 = (i < pc_larger->i_length) ? pc_larger->pi_number[pc_larger->i_length - i - 1] : 0;

        //  Wzięcie kolejnej cyfry drugiej liczby (od końca)
        int i_digit_2 = (i < pc_smaller->i_length) ? pc_smaller->pi_number[pc_smaller->i_length -i - 1] : 0;

        //  Obliczenie wynikowej cyfry z uwzględnieniem pożyczki
        int i_sub = i_digit_1 - i_digit_2 - i_borrow;

        //  Pozbycie się nadmiaru (jeśli wartość i_sub wykracza poza 0-9)
        if (i_sub < 0) {
            i_sub += NUMERIC_SYSTEM_BASE;
            i_borrow = 1;
        }
        else i_borrow = 0;

        c_result.pi_number[c_result.i_length - i - 1] = i_sub;
    }

    c_result.removeLeadingZeros();                              //  Usunięcie zer wiodących, jeśli są
    normalizeZeroSign(c_result);                             //  Jeśli wynik jest równy zero, to ustawiamy znak na dodatni

    return c_result;                                            //  Zwrócenie wyniku
}

//  Operator mnożenia
CNumber CNumber::operator*(const CNumber &pcNewVal) {
    CNumber c_result;

    //  Ustawienie znaku liczy wynikowej na podstawie znaków mnożnej i mnożnika
    c_result.b_is_negative = (b_is_negative != pcNewVal.b_is_negative);

    int i_result_length = i_length + pcNewVal.i_length;          //  Obliczenie długości liczby wynikowej
    delete[] c_result.pi_number;
    c_result.pi_number = new int[i_result_length];

    //  Mnożenie cyfr
    for (int i = 0; i < i_length; i++) {
        int i_digit_1 = pi_number[i_length - i - 1];

        int i_carry = 0;                                         //  Potencjalne przeniesienie

        for (int j = 0; j < pcNewVal.i_length || i_carry > 0; j++) {
            int i_digit_2 = (j < pcNewVal.i_length) ? pcNewVal.pi_number[pcNewVal.i_length - j - 1] : 0;

            int i_sum = c_result.pi_number[i_result_length - i - j - 1] + i_digit_1 * i_digit_2 + i_carry;
            c_result.pi_number[i_result_length - i - j - 1] = i_sum % NUMERIC_SYSTEM_BASE;
            i_carry = i_sum / NUMERIC_SYSTEM_BASE;
        }
    }

    c_result.i_length = i_result_length;                        //  Aktualizacja długości liczby wynikowej
    c_result.removeLeadingZeros();                              //  Usunięcie zer wiodących, jeśli są
    normalizeZeroSign(c_result);                             //  Jeśli wynik jest równy zero to ustawiamy jego znak na dodatni

    return c_result;                                            //  Zwrócenie wyniku
}

//  Operator dzielenia
CNumber CNumber::operator/(const CNumber &pcNewVal) {
    CNumber c_result;

    //  Upewnienie się, że nie wykonuje się dzielenia przez zero
    if (bCheckIfZero(pcNewVal)) {
        std::cout << "Dzielenie przez zero." << std::endl;
        c_result.pi_number = NULL;
        return c_result;
    }

    //  Ustawienie znaku liczy wynikowej na podstawie znaków dzielnej i dzielnika
    c_result.b_is_negative = (b_is_negative != pcNewVal.b_is_negative);

    CNumber c_remainder;                                                        //  Deklaracja reszty
    CNumber c_dividend = *this;                                                 //  Deklaracja i identyfikacja dzielnej
    CNumber c_divisor = pcNewVal;                                                //  Deklaracja i identyfikacja dzielnika

    //  Do obliczeń wykorzystujemy liczby dodatnie, znak wyniku określany jest już wcześniej
    c_dividend.b_is_negative = false;
    c_divisor.b_is_negative = false;

    c_remainder = 0;                                                            //  Inicjalizacja reszty jako zero

    c_result.i_length = c_dividend.i_length;                                    //  Ustalenie długości wynikowej liczby

    if (c_result.i_length <= 0) c_result.i_length = 1;                          //  Jeśli długość wyniku wyjdzie ujemna, to jest ona ustawiana na wartość 1 (wynik będzie równy 0)

    //  Upewnienie się, że pamięć dla liczby wynikowej została zaalokowana poprawnie
    delete[] c_result.pi_number;
    c_result.pi_number = new int[c_result.i_length];

    //  Pętla przechodząca przez każdą cyfrę dzielnej
    for (int i = 0; i < c_dividend.i_length; i++) {
        c_remainder = c_remainder * NUMERIC_SYSTEM_BASE + c_dividend.pi_number[i];      //  Obliczenie aktualnej reszty z dzielenia
        int i_quotient_digit = 0;                                                       //  Inicjalizacja aktualnej cyfry ilorazu jako zero

        //  Pętla wykonuje się tak długo jak reszta jest większa lub równa dzielnikowi
        //  Sprawdzanie ile razy dzielnik mieści się w aktualnie rozpatrywanej reszcie
        while (bIsGreaterOrEqual(c_remainder, c_divisor)) {
            c_remainder = c_remainder - c_divisor;                                      //  Pomniejszenie reszty o jedno mieszczące się w niej wystąpienie dzielnika
            i_quotient_digit++;                                                         //  Inkrementacja aktualnej cyfry ilorazu (licznika mieszczących się dzielników)
        }

        c_result.pi_number[i] = i_quotient_digit;
    }

    c_result.removeLeadingZeros();                              //  Usunięcie zer wiodących jeśli są
    normalizeZeroSign(c_result);                             // Jeśli wynik jest równy zero to ustawiamy jego znak na dodatni

    return c_result;                                            //  Zwrócenie wyniku
}

//  Operator modulo
CNumber CNumber::operator%(const CNumber &pcNewVal) {
    CNumber c_result, c_temp, pcOtherCopy;
    
    pcOtherCopy = pcNewVal;
    c_temp = *this / pcNewVal;
    c_result = *this - (pcOtherCopy * c_temp);

    removeLeadingZeros();
    return c_result;
}

//  --  Operatory dla liczb całkowitych --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

//  Operator przypisania
void CNumber::operator=(const int iNewVal) {
    //  Dealokacja poprzedniej tablicy
    delete[] pi_number;
    i_length = 0;

    b_is_negative = iNewVal < 0;                           //  Sprawdzenie, czy liczba jest dodatnia czy ujemna

    //  Wyliczanie ilości cyfr w podanej liczbie
    int i_digits_quantity_value_copy = iNewVal;            //  Kopia służąca do obliczenia ilości cyfr w liczbie
    int i_normal_value_copy = iNewVal;                     //  Kopia służąca do podziału liczby na cyfry

    do {
        i_digits_quantity_value_copy /= NUMERIC_SYSTEM_BASE;
        i_length++;
    }
    while (i_digits_quantity_value_copy != 0);

    pi_number = new int[i_length];                          //  Alokacja tablicy o nowej długości

    //  Dodawanie cyfr to tablicy (od końca)
    for (int i = i_length - 1; i >= 0; i--) {
        pi_number[i] = abs(i_normal_value_copy) % NUMERIC_SYSTEM_BASE;     //  Wartość absolutna, aby uniknąć powielania znaku "-"
        i_normal_value_copy /= NUMERIC_SYSTEM_BASE;
    }
}

CNumber CNumber::operator+(const int iNewVal) {
    CNumber c_result, c_converted_number;

    c_converted_number = iNewVal;                //  Konwersja typu int na typ CNumber

    c_result = *this + c_converted_number;      //  Wykonanie operacji na typach CNumber

    return c_result;                            //  Zwrócenie wyniku
}

//  Operator odejmowania
CNumber CNumber::operator-(const int iNewVal) {
    CNumber c_result, c_converted_number;

    c_converted_number = iNewVal;                //  Konwersja typu int na typ CNumber

    c_result = *this - c_converted_number;      //  Wykonanie operacji na typach CNumber

    return c_result;                            //  Zwrócenie wyniku
}

//  Operator mnożenia
CNumber CNumber::operator*(const int iNewVal) {
    CNumber c_result, c_converted_number;

    c_converted_number = iNewVal;                //  Konwersja typu int na typ CNumber

    c_result = *this * c_converted_number;      //  Wykonanie operacji na typach CNumber

    return c_result;                            //  Zwrócenie wyniku
}

//  Operator dzielenia
CNumber CNumber::operator/(const int iNewVal) {
    CNumber c_result, c_converted_number;

    c_converted_number = iNewVal;                //  Konwersja typu int na typ CNumber

    c_result = *this / c_converted_number;      //  Wykonanie operacji na typach CNumber

    return c_result;                            //  Zwrócenie wyniku
}

//  Operator modulo
CNumber CNumber::operator%(const int iNewVal) {
    CNumber c_result, c_converted_number;

    c_converted_number = iNewVal;                //  Konwersja typu int na typ CNumber

    c_result = *this % c_converted_number;      //  Wykonanie operacji na typach CNumber

    return c_result;                            //  Zwrócenie wyniku
}

//  --  Pozostałe metody    --------------------------------------------------------------------------------------------

//  Wypisywanie stanu obiektu
std::string CNumber::sToStr() {
    std::string s_result = EMPTY_STRING;        // Inicjalizacja wynikowego napisu jako pusty ("")

    if (b_is_negative) s_result += MINUS_SIGN;  //  Dodanie znaku "-", gdy liczba jest ujemna

    //  Dodanie każdej cyfry do wynikowego napisu
    for (int i = 0; i < i_length; i++) {
        s_result += sIntToString(pi_number[i]);
    }

    return s_result;                            //  Zwrócenie wyniku
}

//  Konwertowanie typu Integer na typ String
std::string CNumber::sIntToString(int i_number) {
    std::ostringstream oss_result;;             //  Strumień wyjściowy 
    oss_result << i_number;                     //  Dodanie liczby do strumienia

    return oss_result.str();                    //  Zwrócenie wyniku
}

//  Usuwanie zer wiodących
void CNumber::removeLeadingZeros() {
    int i_new_length = i_length;

    //  Przesunięcie cyfr w lewo
    while (i_new_length > 1 && pi_number[0] == 0) {
        for (int i = 0; i < i_new_length; i++) {
            pi_number[i] = pi_number[i + 1];
        }

        i_new_length--;                         //  Zmniejszenie długości liczby
    }

    i_length = i_new_length;                    //  Aktualizacja długości liczby
}

//  Ustawianie znaku wyniku jako dodatni, jeśli wynik ten jest równy zero
void CNumber::normalizeZeroSign(CNumber &pcNumber) {
    if (bCheckIfZero(pcNumber)) pcNumber.b_is_negative = false;
}

//  Sprawdzanie czy liczba jest równa zero
bool CNumber::bCheckIfZero(const CNumber &pcNumber) {
    return pcNumber.i_length == 1 && pcNumber.pi_number[0] == 0;
}

//  Sprawdzanie, czy liczba jest więsza lub równa
bool CNumber::bIsGreaterOrEqual(const CNumber &pcNumber1, const CNumber &pcNumber2) {
    return bCompare(pcNumber1, pcNumber2, true);
}

//  Sprawdzanie, czy liczba jest większa
bool CNumber::bIsGreater(const CNumber &pcNumber1, const CNumber &pcNumber2) {
    return bCompare(pcNumber1, pcNumber2, false);
}

//  Uniwersalna metoda do porównywania liczb
bool CNumber::bCompare(const CNumber &pcNumber1, const CNumber &pcNumber2, bool bGreaterOrEqual) {
    if (pcNumber1.b_is_negative && !pcNumber2.b_is_negative) return false;                  //  Liczba pierwsza jest ujemna a druga dodatnia -> druga jest większa
    if (!pcNumber1.b_is_negative && pcNumber2.b_is_negative) return true;                   //  Liczba pierwsza jest dodatnia a druga ujemna -> pierwsza jest większa

    bool b_both_negative = pcNumber1.b_is_negative && pcNumber2.b_is_negative;              //  Ustawienie flagi, określającej czy obie liczby są dodatnie czy obie są ujemne

    if (pcNumber1.i_length > pcNumber2.i_length) return !b_both_negative;                   //  Liczba pierwsza jest dłuższa (większa)
    if (pcNumber1.i_length < pcNumber2.i_length) return b_both_negative;                    //  Liczba druga jest dłuższa (większa)

    //  Jeśli są równej długości to porównujemy ich cyfry od lewej (najbardziej znaczących)
    if (pcNumber1.i_length == pcNumber2.i_length) {
        for (int i = 0; i < pcNumber1.i_length; i++) {
            if (pcNumber1.pi_number[i] > pcNumber2.pi_number[i]) return !b_both_negative;    //  Liczba pierwsza jest większa
            if (pcNumber1.pi_number[i] < pcNumber2.pi_number[i]) return b_both_negative;     //  Liczba druga jest większa
        }
    }

    //  Jeśli liczby są równe, to zwracamy wynik w zależności od wartości flagi
    return bGreaterOrEqual;
}

