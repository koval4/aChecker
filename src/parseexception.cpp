#include "parseexception.h"
#include <exception>
#include <string>

ParseException::ParseException(std::string line, std::string expected, size_t pos)
    : line(line)
    , expected(expected)
    , pos(pos) {
    message = std::string("Unexpected symbol occured at position ")
            + std::to_string(pos)
            + std::string(" in line ")
            + line
            + std::string(", expected ")
            + expected;
}


ParseException::~ParseException() noexcept {}

const char* ParseException::what() const noexcept {
    return message.c_str();
}
