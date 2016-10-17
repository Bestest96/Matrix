#include "MyException.h"

using namespace std;

MyException::MyException(const char* b): blad(b) {};

const char* MyException::what()
{
    return blad;
}

MyException::~MyException() throw() {};
