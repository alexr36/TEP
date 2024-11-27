#include "CError.h"
#include "Constants.h"

//  Konstruktor domyślny
CError::CError() {
    message = ERROR_MESSAGE_DEFAULT_UNKNOWN;
}


//  Konstruktor przeciążony
CError::CError(const std::string &newMessage) {
    message = newMessage;
}


//  Konstruktor kopiujący
CError::CError(const CError &other) {
    message = other.message;
}


//  Destruktor
CError::~CError() {}


//  --  Settery i gettery   --------------------------------------------------------------------------------------------

void CError::setMessage(const std::string &newMessage) {
    message = newMessage;
}


std::string CError::getMessage() {
    return message;
}
