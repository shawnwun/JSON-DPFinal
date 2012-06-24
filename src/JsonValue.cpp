#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include "JsonValue.h"
#include "PrintImp.h"
//#include "JsonException.h"

using namespace std;

PrintImp* JsonValue::_imp;

ostream& operator<< (ostream& os, JsonValue* v) { 
    v->print(os,1);
    return os;
}

// Virtual Functions
void JsonValue::addLeaf(JsonValue* v) {}
void JsonValue::print(ostream &os, int level) {
    JsonValue::_imp->print(os, this, level);
}
JsonValue* JsonValue::getObjectByKey(const string& key){ return NULL;}
JsonValue* JsonValue::getObjectByIndex(const int& index){ return NULL;}


JsonValue::JsonValue() { _type = NullType; };
JsonValue::JsonValue(int i) : _value(i) { _type = IntType; }
JsonValue::JsonValue(double d) : _value(d) { _type = DoubleType; }
JsonValue::JsonValue(bool b) : _value(b) { _type = BoolType; }
JsonValue::JsonValue(string &s) : _value(s) { _type = StringType; }
JsonValue::JsonValue(JsonArray *arr) : _value(arr) {
    //cout << "JsonValue(arr): " << endl;
    _type = ArrayType;
}
JsonValue::JsonValue(JsonObject *obj) : _value(obj) {
    //cout << "JsonValue(obj): " << endl;
    _type = ObjectType;
}
JsonValue::~JsonValue() {
    if (_type == StringType) {
        delete [] _value._string;
    }
}

int JsonValue::asInt() { return _value._int; }
double JsonValue::asDouble() { return _value._double; }
bool JsonValue::asBool() { return _value._bool; }
string JsonValue::asString() { return string(_value._string); }
JsonArray* JsonValue::asJsonArray() { return _value._array; }
JsonObject* JsonValue::asJsonObject() { return _value._object; }
JsonValue::ValueType JsonValue::getType() { return _type; }


JsonValue::_JsonValue::_JsonValue() {}
JsonValue::_JsonValue::_JsonValue(int i) : _int(i) {
    //cout << "_JsonValue(int): " << i << endl;
}
JsonValue::_JsonValue::_JsonValue(double d) : _double(d) {
    //cout << "_JsonValue(double): " << d << endl;
}
JsonValue::_JsonValue::_JsonValue(bool b) : _bool(b) {
    //cout << "_JsonValue(bool): " << b << endl;
}
JsonValue::_JsonValue::_JsonValue(string &str) {
    //cout << "_JsonValue(char*): " << str << endl;
    _string = new char[str.size() + 1];
    strcpy(_string, str.c_str());            
}
//JsonValue::_JsonValue::_JsonValue(JsonArray *arr) : _array(arr) {
//    cout << "_JsonValue(arr): " << endl;
//}
JsonValue::_JsonValue::_JsonValue(JsonArray *arr) {
    //cout << "_JsonValue(arr): " << endl;
    _array = new JsonArray(*arr);
}

//JsonValue::_JsonValue::_JsonValue(JsonObject *obj) : _object(obj) {
//    cout << "_JsonValue(obj): " << endl;
//}
JsonValue::_JsonValue::_JsonValue(JsonObject *obj) {
    //cout << "_JsonValue(obj): " << endl;
    _object = new JsonObject(*obj);
}

/** Pair */
Pair::Pair(string &key, JsonValue *value)
    : _key(key), _value(value) {
}

string& Pair::getKey() { return _key; }
JsonValue* Pair::getValue() { return _value; }
void Pair::print(ostream &os, int level) {
    JsonValue::_imp->print(os, this, level);
}


/** JsonObject */
JsonObject::JsonObject() {}
JsonObject::JsonObject(const JsonObject &rhs) {
    _jsonobj = rhs._jsonobj;
}
//JsonObject(map<string, JsonValue*>& ) {};
//JsonObject(const JsonObject& rhs) {};

int JsonObject::getSize(){
    return _jsonobj.size();
}

map<string, JsonValue*> JsonObject::getObjectMapping(){
    return _jsonobj;
}

void JsonObject::addLeaf(JsonValue* v) {
    Pair *p = (Pair *) v;
    string key = p->getKey().substr(1,p->getKey().size()-2);
    _jsonobj.insert(make_pair(key, p->getValue()));
}

int JsonObject::getInt(const string &key) {
    JSON_OBJECT::const_iterator it = _jsonobj.find(key);
    if (it != _jsonobj.end()) {
        return it->second->asInt();
    } else {  // TODO: throw exception? JsonException?
	cout << "no key: " << key << endl;
        return INT_MIN;
    }
}
string JsonObject::getString(const string &key) {
    JSON_OBJECT::const_iterator it = _jsonobj.find(key);
    if (it != _jsonobj.end()) {
        return it->second->asString();
    } else {  // TODO: throw exception?
        cout << "no key: " << key << endl;
        return string("");
    }
}
JsonValue* JsonObject::getObjectByKey(const string &key) {
    JSON_OBJECT::const_iterator it = _jsonobj.find(key);
    if (it != _jsonobj.end()) {
        return it->second;
    } else {  // TODO: throw exception?
        cout << "no key: " << key << endl;
        return new JsonValue;
    }
}

void JsonObject::print(ostream &os, int level) {
    JsonValue::_imp->print(os, this, level);
}


/** JsonArray */
JsonArray::JsonArray() {}
JsonArray::JsonArray(const JsonArray &rhs) {
    _jsonarr = rhs._jsonarr;
}
// JsonArray(const JsonArray& rhs) {};

vector<JsonValue*> JsonArray::getObjectList(){
    return _jsonarr;
}

JsonValue* JsonArray::getObjectByIndex(const int &index) {
    //TODO
    if(index>=_jsonarr.size()){
	cout << "Json array index out of range!" << endl;
	return new JsonValue;
    }
    else
	return _jsonarr[index];
}

void JsonArray::addLeaf(JsonValue* v) {
    _jsonarr.push_back(v);
}

void JsonArray::print(ostream &os, int level) {
    JsonValue::_imp->print(os, this, level);
}

