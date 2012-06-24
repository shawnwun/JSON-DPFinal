#ifndef PRINT_IMP_H
#define PRINT_IMP_H

#include <iostream>
#include <iomanip>
#include "JsonValue.h"
using namespace std;

class PrintImp{
public:
    virtual void print(ostream&, JsonValue*, int) const = 0;
    virtual void print(ostream&, Pair*, int) const = 0;
    virtual void print(ostream&, JsonObject*, int) const = 0;
    virtual void print(ostream&, JsonArray*, int) const = 0;
};

class DefaultPrintImp : public PrintImp {
public:
    void print(ostream&, JsonValue*, int) const;
    void print(ostream&, Pair*, int) const;
    void print(ostream&, JsonObject*, int) const;
    void print(ostream&, JsonArray*, int) const;
};

class PrettyPrintImp : public PrintImp {
public:
    PrettyPrintImp(int sep):_sep(sep){}
    void print(ostream&, JsonValue*, int) const;
    void print(ostream&, Pair*, int) const;
    void print(ostream&, JsonObject*, int) const;
    void print(ostream&, JsonArray*, int) const;
private:
    int _sep;
};




#endif

