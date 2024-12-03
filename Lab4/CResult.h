#ifndef CRESULT_H
#define CRESULT_H
#include <vector>

//  --  Definicja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T, typename E>
class CResult {
    public:
        CResult(const T &newValue);                                                                                     //  Konstruktor dla wyniku
        CResult(E *newError);                                                                                           //  Konstruktor dla pojedynczego błędu
        CResult(std::vector<E*> newErrors);                                                                             //  Konstruktor dla wektora błędów
        CResult(const CResult<T, E> &other);                                                                            //  Konstruktor kopiujący

        ~CResult();                                                                                                     //  Destruktor

        static CResult<T, E> ok(const T &newValue);                                                                     //  Zgłoszenie poprawnego wyniku
        static CResult<T, E> fail(E *newError);                                                                         //  Zgłoszenie pojedynczego błędu
        static CResult<T, E> fail(std::vector<E*> &newErrors);                                                          //  Zgłoszenie wektora błędów

        CResult<T, E>& operator=(const CResult<T, E> &other);                                                           //  Operator przypisania

        //  Settery i gettery
        bool isSuccess();

        T getValue();
        std::vector<E*>& getErrors();

    private:
        void copyResult(const CResult<T, E> &other);                                                                    //  Kopiowanie zawartości wyniku
        void clear(const CResult<T, E> &other);

        T* value;                                                                                                       //  Wartość właściwa wyniku
        std::vector<E*> errors;                                                                                         //  Wektor błędów
        bool success;                                                                                                   //  Flaga sukcesu
};

//  --  Implementacja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T, typename E>
CResult<T, E>::CResult(const T &newValue) {                                                                             //  Konstruktor dla wyniku
    value = new T(newValue);
    success = true;
}


template<typename T, typename E>
CResult<T, E>::CResult(E *newError) {                                                                                   //  Konstruktor dla pojedynczego błędu
    errors.push_back(newError);
    success = false;
}


template<typename T, typename E>
CResult<T, E>::CResult(std::vector<E*> newErrors) {                                                                     //  Konstruktor dla wektora błędów
    for (int i = 0; i < newErrors.size(); i++) {
        errors.push_back(newErrors[i]);
    }

    success = false;
}


template<typename T, typename E>
CResult<T, E>::CResult(const CResult<T, E> &other) {                                                                    //  Konstruktor kopiujący
    copyResult(other);
}


template<typename T, typename E>
CResult<T, E>::~CResult() {                                                                                             //  Destruktor
    delete value;                                                                                                       //  Zwolnienie wskaźnika wartości

    clear(*this);
}


template<typename T, typename E>
CResult<T, E> CResult<T, E>::ok(const T &newValue) {                                                                    //  Zgłoszenie poprawnego wyniku
    return CResult<T, E>(newValue);
}


template<typename T, typename E>
CResult<T, E> CResult<T, E>::fail(E *newError) {                                                                        //  Zgłoszenie pojedynczego błędu
    return CResult<T, E>(newError);
}


template<typename T, typename E>
CResult<T, E> CResult<T, E>::fail(std::vector<E*> &newErrors) {                                                         //  Konstruktor dla wektora błędów
    return CResult<T, E>(newErrors);
}


template<typename T, typename E>
CResult<T, E>& CResult<T, E>::operator=(const CResult<T, E> &other) {                                                   //  Operator przypisania
    if (this != &other) {                                                                                               //  Zabezpieczenie przed samoprzydzielaniem
        delete value;                                                                                                   //  Zwolnienie wskaźnika wartości

        clear(other);

        copyResult(other);                                                                                              //  Skopiowanie zawartości wyniku
    }

    return *this;                                                                                                       //  Zwrócenie wyniku
}


template<typename T, typename E>
bool CResult<T, E>::isSuccess() {
    return success;
}


template<typename T, typename E>
T CResult<T, E>::getValue() {
    if (success && value != NULL) return *value;

    return T();
}


template<typename T, typename E>
std::vector<E*>& CResult<T, E>::getErrors() {
    return errors;
}


template<typename T, typename E>
void CResult<T, E>::copyResult(const CResult<T, E> &other) {                                                            //  Kopiowanie zawartości wyniku
    value = (other.value ? new T(*other.value) : 0);
    errors = other.errors;
    success = other.success;
}


template<typename T, typename E>
void CResult<T, E>::clear(const CResult<T, E> &other) {
    for (typename std::vector<E*>::const_iterator it = other.errors.begin(); it != other.errors.end(); it++) {          //  Dla każdego błędu w wektorze błędów
        if (*it != NULL) delete *it;                                                                                    //  Jeśli bład istnieje to usunięcie go
    }
}


//  --  Specjalizacja dla typu void ------------------------------------------------------------------------------------

//  --  Definicja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename E>
class CResult<void, E> {
public:
    CResult();                                                                                                          //  Konstruktor dla wyniku
    CResult(E *newError);                                                                                               //  Konstruktor dla pojedynczego błędu
    CResult(std::vector<E*> newErrors);                                                                                 //  Konstruktor dla wektora błędów
    CResult(const CResult<void, E> &other);                                                                             //  Konstruktor kopiujący

    ~CResult();                                                                                                         //  Destruktor

    static CResult<void, E> ok();                                                                                       //  Zgłoszenie poprawnego wyniku
    static CResult<void, E> fail(E *newError);                                                                          //  Zgłoszenie pojedynczego błędu
    static CResult<void, E> fail(std::vector<E*> &newErrors);                                                           //  Zgłoszenie wektora błędów

    CResult<void, E>& operator=(const CResult<void, E> &other);                                                         //  Operator przypisania

    //  Settery i gettery
    bool isSuccess();

    std::vector<E*>& getErrors();

private:
    void copyResult(const CResult<void, E> &other);                                                                     //  Kopiowanie zawartości wyniku

    std::vector<E*> errors;                                                                                             //  Wektor błędów
    bool success;                                                                                                       //  Flaga sukcesu
};

//  --  Implementacja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename E>
CResult<void, E>::CResult() {                                                                                           //  Konstruktor dla wyniku
    success = true;
}


template<typename E>
CResult<void, E>::CResult(E *newError) {                                                                                //  Konstruktor dla pojedynczego błędu
    errors.push_back(newError);
    success = false;
}


template<typename E>
CResult<void, E>::CResult(std::vector<E *> newErrors) {                                                                 //  Konstruktor dla wektora błędów
    errors + newErrors;
    success = false;
}


template<typename E>
CResult<void, E>::CResult(const CResult<void, E> &other) {                                                              //  Konstruktor kopiujący
    copyResult(other);
}


template<typename E>
CResult<void, E>::~CResult() {                                                                                          //  Destruktor
    for (typename std::vector<E*>::iterator it = errors.begin(); it != errors.end(); it++) {                            //  Dla każdego błędu w wektorze błędów
        if (*it != NULL) delete *it;                                                                                    //  Jeśli bład istnieje to usuń go
    }
}


template<typename E>
CResult<void, E> CResult<void, E>::ok() {                                                                               //  Zgłoszenie poprawnego wyniku
    return CResult<void, E>();
}


template<typename E>
CResult<void, E> CResult<void, E>::fail(E *newError) {                                                                  //  Zgłoszenie pojedynczego błędu
    return CResult<void, E>(newError);
}


template<typename E>
CResult<void, E> CResult<void, E>::fail(std::vector<E *> &newErrors) {                                                  //  Zgłoszenie wektora błędów
    return CResult<void, E>(newErrors);
}


template<typename E>
CResult<void, E> &CResult<void, E>::operator=(const CResult<void, E> &other) {                                          //  Operator przypisania
    if (this != &other) {                                                                                               //  Zabezpieczenie przed samoprzydzielaniem
        for (typename std::vector<E*>::iterator it = other.errors.begin(); it != other.errors.end(); it++) {            //  Dla każdego błędu w wektorze błędów
            if (*it != NULL) delete *it;                                                                                //  Jeśli bład istnieje to usunięcie go
        }

        copyResult(other);                                                                                              //  Skopiowanie zawartości wyniku
    }

    return *this;                                                                                                       //  Zwrócenie wyniku
}


template<typename E>
bool CResult<void, E>::isSuccess() {
    return success;
}


template<typename E>
std::vector<E *> &CResult<void, E>::getErrors() {
    return errors;
}


template<typename E>
void CResult<void, E>::copyResult(const CResult<void, E> &other) {                                                      //  Kopiowanie zawartości wyniku
    errors = other.errors;
    success = other.success;
}

//  --  Modyfikacja ----------------------------------------------------------------------------------------------------

//  --  Definicja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T, typename E>
class CResult<T*, E> {
    public:
        CResult(T* newValue);
        CResult(E* newError);
        CResult(std::vector<E*> &newErrors);
        CResult(const CResult<T*, E> &other);

        ~CResult();

        CResult<T*, E>& operator=(const CResult<T*, E> &other);

        template<typename TOther>
        CResult<TOther*, E> toResult(TOther* value);

        bool isSuccess();

        T* getValue();
        std::vector<E*>& getErrors();

    private:
        void copyResult(const CResult<T*, E> &other);
        void clear();

        T* value;
        std::vector<E*> errors;
        bool success;
};

//  --  Implementacja klasy --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

template<typename T, typename E>
CResult<T*, E>::CResult(T* newValue) {                                                                                  //  Konstruktor dla wyniku
    value = newValue;
    success = true;
}


template<typename T, typename E>
CResult<T*, E>::CResult(E *newError) {                                                                                  //  Konstruktor dla pojedynczego błędu
    if (newError) {
        errors.push_back(new E(*newError));
    }

    success = false;
    value = NULL;
}


template<typename T, typename E>
CResult<T*, E>::CResult(std::vector<E*> &newErrors) {                                                                   //  Konstruktor dla wektora błędów
    for (typename std::vector<E*>::iterator it = newErrors.begin(); it != newErrors.end(); it++) {
        if (*it) errors.push_back(new E(**it));
    }

    success = false;
    value = NULL;
}


template<typename T, typename E>
CResult<T*, E>::CResult(const CResult<T*, E> &other) {                                                                  //  Konstruktor kopiujący
    copyResult(other);
}


template<typename T, typename E>
CResult<T*, E>::~CResult() {                                                                                            //  Destruktor
    clear();
}


template<typename T, typename E>
CResult<T*, E>& CResult<T*, E>::operator=(const CResult<T*, E> &other) {                                                //  Operator przypisania
    if (this != &other) {
        clear();
        copyResult(other);
    }

    return *this;                                                                                                       //  Zwrócenie wyniku
}


template<typename T, typename E>
template<typename TOther>
CResult<TOther*, E> CResult<T*, E>::toResult(TOther *newValue) {
    if (success) return CResult<TOther*, E>(newValue);

    delete newValue;

    return CResult<TOther*, E>(errors);
}



template<typename T, typename E>
bool CResult<T*, E>::isSuccess() {
    return success;
}


template<typename T, typename E>
T* CResult<T*, E>::getValue() {
    return (success && value) ? value : NULL;
}


template<typename T, typename E>
std::vector<E*>& CResult<T*, E>::getErrors() {
    return errors;
}


template<typename T, typename E>
void CResult<T*, E>::copyResult(const CResult<T*, E> &other) {                                                          //  Kopiowanie zawartości wyniku
    if (other.value) {
        value = new T(*other.value);
    }
    else {
        value = NULL;
    }

    for (typename std::vector<E*>::const_iterator it = other.errors.begin(); it != other.errors.end(); it++) {
        if (*it) errors.push_back(new E(**it));
    }

    success = other.success;
}


template<typename T, typename E>
void CResult<T *, E>::clear() {
    delete value;
    value = NULL;

    for (typename std::vector<E*>::iterator it = errors.begin(); it != errors.end(); it++) {
        if (*it) delete *it;
    }

    errors.clear();
}


#endif //CRESULT_H
