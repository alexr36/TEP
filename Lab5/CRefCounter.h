#ifndef CREFCOUNTER_H
#define CREFCOUNTER_H

//  Klasa licznika referencji
class CRefCounter {
    public:
        CRefCounter();                                                                                                  //  Konstruktor domyślny

        int add();                                                                                                      //  Inkrementacja licznika
        int dec();                                                                                                      //  Dekrementacja licznika
        int get();                                                                                                      //  Zwrócenie wartości licznika

    private:
        int count;                                                                                                      //  Wartość licznika
};

#endif //CREFCOUNTER_H
