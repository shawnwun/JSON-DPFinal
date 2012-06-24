#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <string>
#include <map>
#include <vector>
using namespace std;

class JsonArray;
class JsonObject;

class JsonValue {
public:
    virtual void addLeaf(JsonValue* v);
    JsonValue();
    JsonValue(int i);
    JsonValue(double d);
    JsonValue(bool b);
    JsonValue(string &s);
    JsonValue(JsonArray *arr);
    JsonValue(JsonObject *obj);
    ~JsonValue();

    int asInt();
    double asDouble();
    bool asBool();
    string asString();
    JsonArray* asJsonArray();
    JsonObject* asJsonObject();
    //ValueType getType();
    virtual void print(ostream &, int level);

    friend ostream& operator<< (ostream& os, JsonValue* v);

    enum ValueType {            
        IntType, DoubleType, BoolType,
        StringType, NullType,
        ObjectType, ArrayType
    };

private:
    typedef union _JsonValue {
        _JsonValue();
        _JsonValue(int i);
        _JsonValue(double d);
        _JsonValue(bool b);
        _JsonValue(string &str);
        _JsonValue(JsonArray *arr);
        _JsonValue(JsonObject *obj);

        int _int;
        double _double;
        bool _bool;
        char *_string;
        JsonArray *_array;
        JsonObject *_object;

    } Value;    

    Value _value;
    ValueType _type;
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
    //JsonObject(map<string, JsonValue*>& ) {};
    //JsonObject(const JsonObject& rhs) {};

    virtual void addLeaf(JsonValue* v);

    int getInt(const string &key);
    string getString(const string &key);
    JsonObject* getJsonObject(const string &key);


    virtual void print(ostream &, int level);

private:
    JSON_OBJECT _jsonobj;
};


class JsonArray : public JsonValue {
public:
    JsonArray();
    JsonArray(const JsonArray &rhs);
    // JsonArray(const JsonArray& rhs) {};

    virtual void addLeaf(JsonValue* v);
    virtual void print(ostream &, int level);

private:
    vector<JsonValue*> _jsonarr;
};


#endif

