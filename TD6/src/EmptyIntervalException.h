#ifndef INTLIB_EMPTYINTERVALEXCEPTION_H
#define INTLIB_EMPTYINTERVALEXCEPTION_H

#include <exception>

struct EmptyIntervalException: public std::exception {
    [[nodiscard]] const char* what() const noexcept override{
        return "Empty Interval Exception";
    }
};


#endif //INTLIB_EMPTYINTERVALEXCEPTION_H
