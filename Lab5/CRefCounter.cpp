#include "CRefCounter.h"

//  Konstruktor domyślny
CRefCounter::CRefCounter() {
    count = 0;
}

//  Inkrementacja licznika
int CRefCounter::add() {
    return ++count;
}

//  Dekrementacja licznika
int CRefCounter::dec() {
    return --count;
}

//  Zwrócenie wartości licznika
int CRefCounter::get() {
    return count;
}

