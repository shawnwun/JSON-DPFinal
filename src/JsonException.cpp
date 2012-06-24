#include "JsonException.h"

const char* JsonException::what() const throw(){
    return "[JsonException]: Unknown exception";
}

const char* IncorrectJsonException::what() const throw(){
    return "[JsonException]: Incorrect Json format";
}

const char* NotJsonObjectException::what() const throw(){
    return "[JsonException]: Target is not a JsonObject";
}

const char* NotJsonArrayException::what() const throw(){
    return "[JsonException]: Target is not a JsonArray";
}

const char* DataNotFoundException::what() const throw(){
    return "[JsonException]: The requested data doesn't exist";
}


