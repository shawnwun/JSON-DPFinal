#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H


#include <exception>

class JsonException{
public:
    virtual const char* what() const throw();
};

class IncorrectJsonException : JsonException {
public:
    virtual const char* what() const throw();
};

class NotJsonObjectException : JsonException {
public:
    virtual const char* what() const throw();
};

class NotJsonArrayException : JsonException {
public:
    virtual const char* what() const throw();
};

class DataNotFoundException : JsonException {
public:
    virtual const char* what() const throw();
};



#endif

