#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <map>
#include <vector>
using namespace std;

class JsonValue {
public:
    virtual void addLeaf(JsonValue*) {};
    JsonValue() {};
    ~JsonValue() {};
};

class String : public JsonValue {
public:
    String(string s) : _str(s) {}
    virtual void addLeaf(JsonValue* v) {}
    
private:
    string _str;
};

class Number : public JsonValue {
public:
    Number(int i) : _number(i) {}
    Number(double d) : _number(d) {}
    virtual void addLeaf(JsonValue* v) {}

private:
    union _Number {
        _Number(int i) : _int(i) {}
        _Number(double i) : _double(i) {}

        int _int;
        double _double;
    } _number;
};

class Boolean : public JsonValue {
public:
    Boolean(bool b):_bool(b) {}
    virtual void addLeaf(JsonValue* v) {}

private:
    bool _bool;
};

/** simple wrapper */
class Null : public JsonValue {
public:
    Null() : _ptr(NULL) {}
    virtual void addLeaf(JsonValue* v) {}

private:
    char *_ptr;
};

class Pair : public JsonValue {
public:
    Pair(pair<String*, JsonValue*> &p) : _pair(p) {}
    virtual void addLeaf(JsonValue* v) {}

    pair<String*, JsonValue*>& asPair() {
        return _pair;
    }

private:
    pair<String*, JsonValue*> _pair;
};

class JsonObject : public JsonValue {
public:
    JsonObject() {};
    JsonObject(map<String*, JsonValue*>& ) {};

    virtual void addLeaf(JsonValue* v) {
        Pair *jsonPair = (Pair *) v;
        _jsonobj.insert(jsonPair->asPair());
    }

private:
    map<String*, JsonValue*> _jsonobj;
};


class JsonArray : public JsonValue {
public:
    JsonArray() {};
    JsonArray(vector<JsonValue*>& ) {};

    virtual void addLeaf(JsonValue* v) {
        _jsonarr.push_back(v);
    }

private:
    vector<JsonValue*> _jsonarr;
};
#endif

