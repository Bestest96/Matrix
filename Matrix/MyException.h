#pragma once

#include <exception>

class MyException: public std::exception
{
public:
    const char* what();
    MyException(const char*);
    ~MyException() throw();
private:
    const char* blad;
};
