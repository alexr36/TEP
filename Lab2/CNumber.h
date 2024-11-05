#ifndef CNUMBER_H
#define CNUMBER_H
#include <string>

class CNumber {
    public:
        CNumber();                                          //  Konstruktor domyślny
        CNumber(const CNumber &pcOther);                    //  Konstruktor kopiujący
        ~CNumber();                                         //  Destruktor

        //  --  Operatory   --------------------------------------------------------------------------------------------

        //  Dla obiektów klasy
        void operator=(const CNumber &pcNewVal);            //  Operator przypisania
        CNumber operator+(const CNumber &pcNewVal);         //  Operator dodawania
        CNumber operator-(const CNumber &pcNewVal);         //  Operator odejmowania
        CNumber operator*(const CNumber &pcNewVal);         //  Operator mnożenia
        CNumber operator/(const CNumber &pcNewVal);         //  Operator dzielenia
        CNumber operator%(const CNumber &pcNewVal);         //  Operator modulo

        //  Dla liczb całkowitych
        void operator=(int iNewVal);                        //  Operator przypisania
        CNumber operator+(int iNewVal);                     //  Operator dodawania
        CNumber operator-(int iNewVal);                     //  Operator odejmowania
        CNumber operator*(int iNewVal);                     //  Operator mnożenia
        CNumber operator/(int iNewVal);                     //  Operator dzielenia
        CNumber operator%(int iNewVal);                     //  Operator modulo

        //  Modyfikacja
        CNumber operator^(int iDigitToRemove);              //  Operator usuwający w określone cyfry wiodące

        //  --  Gettery i settery   ------------------------------------------------------------------------------------
        void vSetLength(int iNewLength);
        void vSetIsNegative(bool bIsNegative);
        void vSetNumber(int* piNewNumber);

        int iGetLength();
        bool bIsNegative();
        int* piGetNumber();

        //  Pozostałe metody
        std::string sToStr();                               //  Wypisywanie stanu obiektu na ekran
        bool bCheckIfZero(const CNumber &pcNumber);         //  Sprawdzanie czy liczba jest równa zero
        bool bIsGreaterOrEqual(const CNumber &pcNumber1, const CNumber &pcNumber2);   //  Sprawdzanie, czy liczba jest więsza lub równa
        bool bIsGreater(const CNumber &pcNumber1, const CNumber &pcNumber2);          //  Sprawdzanie, czy liczba jest równa

    private:
        bool bCompare(const CNumber &pcNumber1, const CNumber &pcNumber2, bool bGreaterOrEqual);    //  Porównanie liczb z flagą bGreaterOrEqual
        void removeLeadingZeros();                          //  Usuwanie zer wiodących
        void normalizeZeroSign(CNumber &pcNumber);          //  Jeśli wynik jest zerem, to jego znak jest dodatni
        std::string sIntToString(int i_number);             // Konwetrowanie typu Integer na typ String
        void vPrintDivideByZeroInfo(const CNumber &pcNumber, CNumber &c_result);
        void vCopyFrom(const CNumber &pcOther);

        //  Pola klasy
        int i_length;                                       //  Długość liczby
        int* pi_number;                                     //  Wskaźnik na tablicę cyfr
        bool b_is_negative;                                 //  Identyfikator znaku liczby
};

#endif //CNUMBER_H
