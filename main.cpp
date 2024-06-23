#include "Interface.h"
#include <iostream>

int main()
{
    Interface interface;

    try {

        interface.Run();
    }
    catch (const String& errormessage) {
        ErrorHandler::getInstance().logError(errormessage);
        if (ErrorHandler::getInstance().hasErrors()) {
            std::cout << "Errors occurred during parsing:" << std::endl;
            ErrorHandler::getInstance().printErrors();
        }
        //std::cout << "Hello World!\n";
    }
}