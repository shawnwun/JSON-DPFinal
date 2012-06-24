#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <string>
#include <map>
#include <vector>
#include "JsonException.h"
using namespace std;

class JsonArray;
class JsonObject;

class PrintImp;
class PrettyPrintImp;
class DefaultPrintImp;

class JsonValue {
public:
    
    virtual void addLeaf(JsonValue* v);
    virtual void print(ostream &, int level);
    virtual JsonValue* getObjectByKey(const string& key);
    virtual JsonValue* getObjectByIndex(const int& index);
    
    friend ostream& operator<< (ostream& os, JsonValue* v);

    // Config function
    static void ConfigImp(PrintImp* imp){
	_imp = imp;
    }

protected:
    // Print Imp.
    static PrintImp* _imp;
};

class JsonNull : public JsonValue{
public:
    virtual void print(ostream &, int level);
};


class JsonString : public JsonValue{
public:
    JsonString(string s):_str(s){} 
    string getString(){ return _str;}

    virtual void print(ostream &, int level);

private:
    string _str;
};

class JsonBoolean : public JsonValue{
public:
    JsonBoolean(double b):_bool(b){} 
    bool getBoolean(){ return _bool;}

    virtual void print(ostream &, int level);

private:
    bool _bool;
};

class JsonDouble : public JsonValue{
public:
    JsonDouble(double d):_double(d){} 
    double getDouble(){ return _double;}

    virtual void print(ostream &, int level);

private:
    double _double;
};

class Pair : public JsonValue {
public:
    Pair(string &key, JsonValue *value);

    string& getKey();
    JsonValue* getValue();
    virtual void print(ostream &, int level);

private:
    string _key;
    JsonValue *_value;
};

class JsonObject : public JsonValue {
public:
    typedef map<string, JsonValue*> JSON_OBJECT;

    JsonObject();
    JsonObject(const JsonObject &rhs);

    virtual void addLeaf(JsonValue* v);
    virtual JsonValue* getObjectByKey(const string &key);
    virtual void print(ostream &, int level);
    
    int getSize();
    //int getInt(const string &key);
    //string getString(const string &key);
    JSON_OBJECT getObjectMapping(); 


private:
    JSON_OBJECT _jsonobj;
};


class JsonArray : public JsonValue {
public:
    JsonArray();
    JsonArray(const JsonArray &rhs);
    // JsonArray(const JsonArray& rhs) {};

    vector<JsonValue*> getObjectList();

    virtual void addLeaf(JsonValue* v);
    virtual void print(ostream &, int level);
    virtual JsonValue* getObjectByIndex(const int& index);

private:
    vector<JsonValue*> _jsonarr;
};


#endif

