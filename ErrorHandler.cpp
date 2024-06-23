#include "ErrorHandler.h"
void ErrorHandler::logError(const String& error) {
    errors.Add(error);
}
void ErrorHandler::logError(int error) {
    String temp;
    temp.IntToString(error);
    errors.Add(error);
}
void ErrorHandler::printErrors() const {
    if (errors.isEmpty()) {
        std::cout << "No errors logged." << std::endl;
    }
    else {
        std::cout << "Logged errors:" << std::endl;
        for (int i = 0; i < errors.getSize(); ++i) {
            std::cout << errors[i] << std::endl;
        }
    }
}

bool ErrorHandler::hasErrors() const {
    return !errors.isEmpty();
}