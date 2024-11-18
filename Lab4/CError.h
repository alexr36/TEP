#ifndef CERROR_H
#define CERROR_H
#include <string>


class CError {
    public:
        CError(const std::string& newMessage);
        CError(const CError& other);
        ~CError();

        void setMessage(std::string newMessage);
        std::string getMessage();

    private:
        std::string message;
};



#endif //CERROR_H
