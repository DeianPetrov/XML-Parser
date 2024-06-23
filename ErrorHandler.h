#pragma once
#include "MyString.h"
#include "Array.hpp"
class ErrorHandler {
    Array<String> errors;

public:
    void logError(const String& error);
    void logError(int error);
    void printErrors() const;
    bool hasErrors() const;
    static ErrorHandler& getInstance() {
        static ErrorHandler instance;
        return instance;
    }
};