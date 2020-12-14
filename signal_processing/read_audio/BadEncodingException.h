//
// Created by salyd on 11/12/2020.
//

#ifndef SIGNAL_PROCESSING_BADENCODINGEXCEPTION_H
#define SIGNAL_PROCESSING_BADENCODINGEXCEPTION_H


#include <exception>
#include <utility>

class BadEncodingException : public std::exception {
public:
    explicit BadEncodingException(std::string message) noexcept: message(std::move(message)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};


#endif //SIGNAL_PROCESSING_BADENCODINGEXCEPTION_H
