#ifndef CMYSMARTPOINTER_H
#define CMYSMARTPOINTER_H
#include "CRefCounter.h"

//  Klasa inteligentnego wskaźnika

//  --  Definicja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T, typename CRefCounter>
class CMySmartPointer {
    public:
        CMySmartPointer(T* ptr);                                                                                        //  Konstruktor przeciążony
        CMySmartPointer(const CMySmartPointer &other);                                                                  //  Konstruktor kopiujący

        ~CMySmartPointer();                                                                                             //  Destruktor

        T& operator*();                                                                                                 //  Operator '*'
        T* operator->();                                                                                                //  Operator '->'

        CMySmartPointer& operator=(const CMySmartPointer &other);                                                       //  Operator przypisania

    private:
        void copy(const CMySmartPointer &other);                                                                        //  Metoda pomocnicza do kopiowania zawartości obiektu wskaźnika inteligentnego
        void release();                                                                                                 //  Metoda pomocnicza do zwalniania pamięci wskazywanej przez wskaźnik

        T* ptr;                                                                                                         //  Przechowywany wskaźnik
        CRefCounter* counter;                                                                                           //  Wskaźnik na licznik odwołań
        bool is_dynamic;                                                                                                //  Flaga dynamicznej alokacji obiektu, na który wskazuje wskaźnik
};

//  --  Implementacja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T, typename U>
CMySmartPointer<T, U>::CMySmartPointer(T *newPtr) {                                                                     //  Konstruktor przeciążony
    ptr = newPtr;
    counter = new CRefCounter();
    counter->add();
    is_dynamic = true;
}

template<typename T, typename CRefCounter>
CMySmartPointer<T, CRefCounter>::CMySmartPointer(const CMySmartPointer &other) {                                        //  Konstruktor kopiujący
    copy(other);                                                                                                        //  Skopiowanie wskaźnika
}

template<typename T, typename CRefCounter>
CMySmartPointer<T, CRefCounter>::~CMySmartPointer() {                                                                   //  Destruktor
    release();                                                                                                          //  Zwolnienie wskaźnika
}

template<typename T, typename CRefCounter>
T& CMySmartPointer<T, CRefCounter>::operator*() {                                                                       //  Operator '*'
    return *ptr;
}

template<typename T, typename CRefCounter>
T *CMySmartPointer<T, CRefCounter>::operator->() {                                                                      //  Operator '->'
    return ptr;
}

template<typename T, typename CRefCounter>
CMySmartPointer<T, CRefCounter>& CMySmartPointer<T, CRefCounter>::operator=(const CMySmartPointer &other) {             //  Operator przypisania
    if (this != &other) {                                                                                               //  Zabezpieczenie przed samoprzydzielaniem
        release();                                                                                                      //  Zwolnienie wskaźnika
        copy(other);                                                                                                    //  Skopiowanie drugiego wskaźnika
    }

    return *this;                                                                                                       //  Zwrócenie wyniku
}

template<typename T, typename CRefCounter>
void CMySmartPointer<T, CRefCounter>::copy(const CMySmartPointer &other) {                                              //  Metoda pomocnicza do kopiowania zawartości obiektu wskaźnika inteligentnego
    ptr = other.ptr;
    counter = other.counter;
    counter->add();
    is_dynamic = other.is_dynamic;
}

template<typename T, typename CRefCounter>
void CMySmartPointer<T, CRefCounter>::release() {                                                                       //  Metoda pomocnicza do zwalniania pamięci wskazywanej przez wskaźnik
    if (counter->dec() == 0) {                                                                                          //  Jeśli licznik referencji jest równy 0 po dekrementacji:
        if (is_dynamic) delete ptr;                                                                                     //  Jeśli pamięć została zaalokowana dynamicznie, zwolnij wskaźnik

        delete counter;                                                                                                 //  Zwolnij wskaźnik na licznik referencji
    }
}


#endif //CMYSMARTPOINTER_H
