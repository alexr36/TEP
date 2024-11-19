#include "CError.h"

CError::CError(const std::string &newMessage) {
    message = newMessage;
}

CError::CError(const CError &other) {
    message = other.message;
}

CError::~CError() {}


void CError::setMessage(std::string newMessage) {
    message = newMessage;
}

std::string CError::getMessage() {
    return message;
}