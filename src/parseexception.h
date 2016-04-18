#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <exception>
#include <string>

class ParseException : public std::exception {
    private:
        std::string message;
        std::string line;
        std::string expected;
        size_t pos;

    public:
        ParseException(std::string line, std::string expected, size_t pos);
        virtual ~ParseException() noexcept;

    // exception interface
    public:
        virtual const char* what() const noexcept override;
};

#endif // PARSEEXCEPTION_H
