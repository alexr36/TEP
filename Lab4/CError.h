#ifndef CERROR_H
#define CERROR_H

#include <string>

class CError {
    public:
        CError();                                                                                                       //  Konstruktor domyślny
        CError(const std::string& newMessage);                                                                          //  Konstruktor przeciążony
        CError(const CError& other);                                                                                    //  Konstruktor kopiujący
        ~CError();                                                                                                      //  Destruktor

        //  Settery i gettery
        void setMessage(const std::string& newMessage);
        std::string getMessage();

    private:
        std::string message;                                                                                            //  Opis błędu
};



#endif //CERROR_H
