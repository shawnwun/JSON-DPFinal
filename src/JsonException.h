#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H


#include <exception>

class JsonException : public exception {
public:
    virtual const char* what() const throw(){ return "[JsonException]: Unknown exception"; }
} excep;

class IncorrectJsonException : JsonException {
public:
    virtual const char* what() const throw(){ return "[JsonException]: Incorrect Json format"; }
} incorrexcep;

class NotJsonObjectException : JsonException {
public:
    virtual const char* what() const throw(){ return "[JsonException]: Target is not a JsonObject"; }
} notobjexcep;

class NotJsonArrayException : JsonException {
public:
    virtual const char* what() const throw(){ return "[JsonException]: Target is not a JsonArray"; }
} notarrexcep;

class DataNotFoundException : JsonException {
public:
    virtual const char* what() const throw(){ return "[JsonException]: The data is not exist"; }
} datanfoundexcep;



#endif

