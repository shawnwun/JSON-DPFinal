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
JsonValue* JsonValue::getObjectByKey(const string& key){
    try{
	NotJsonObjectException notobjexcep;
	throw notobjexcep;
	return new JsonNull();
    } catch(NotJsonObjectException& exception){
	cout << exception.what() << endl;
    }
    return new JsonNull();
}
JsonValue* JsonValue::getObjectByIndex(const int& index){
    try{
	NotJsonArrayException notarrexcep;
	throw notarrexcep;
	return new JsonNull();
    } catch(NotJsonArrayException& exception){
	cout << exception.what() << endl;
    }
    return new JsonNull();
}

/** JsonNull **/
void JsonNull::print(ostream &os, int level){
    os << "null";
}

/** JsonBoolean **/
void JsonBoolean::print(ostream &os, int level){
    os << (_bool ? "true" : "false");
}
/** JsonString **/
void JsonString::print(ostream &os, int level){
    os << _str;
}
/** JsonDouble **/
void JsonDouble::print(ostream &os, int level){
    os << _double;
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

JsonValue* JsonObject::getObjectByKey(const string &key) {
    JSON_OBJECT::const_iterator it = _jsonobj.find(key);
    try{
	if (it != _jsonobj.end()) {
	    return it->second;
	} 
	else{
	    DataNotFoundException datanfoundexcep;
	    throw datanfoundexcep;
	    return new JsonNull();
	}
    } catch(DataNotFoundException& exception){
	cout << exception.what() << endl;
    }
    return new JsonNull();
}

void JsonObject::print(ostream &os, int level) {
    JsonValue::_imp->print(os, this, level);
}


/** JsonArray */
JsonArray::JsonArray() {}
JsonArray::JsonArray(const JsonArray &rhs) {
    _jsonarr = rhs._jsonarr;
}

vector<JsonValue*> JsonArray::getObjectList(){
    return _jsonarr;
}

JsonValue* JsonArray::getObjectByIndex(const int &index) {
    try{
	if(index>=_jsonarr.size()){
	    DataNotFoundException datanfoundexcep;
	    throw datanfoundexcep;
	    return new JsonNull();
	}
	else return _jsonarr[index];
    } catch(DataNotFoundException& exception){
	cout << exception.what() << endl;
    }
    return new JsonNull();
}

void JsonArray::addLeaf(JsonValue* v) {
    _jsonarr.push_back(v);
}

void JsonArray::print(ostream &os, int level) {
    JsonValue::_imp->print(os, this, level);
}

