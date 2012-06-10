#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
protected:
    Object(){}
    ~Object(){} 
}

class Primitive : public Object{
public:
    
};

class String : public Object {
public:
    String(string s):_str(s){}
    

private:
    string _str;
};

class Integer : public Object{
public:
    Integer(int i):_int(i){}

private:
    int _int;
};

class Float : public Object{
public:
    Float(float f):_float(f){}

private:
    float _float;
};

class Double : public Object{
public:
    Double(double d):_double(d){}

private:
    double _double;
};

class Boolean : public Object{
public:
    Boolean(bool b):_bool(b){}

private:
    bool _bool;
};

#endif

