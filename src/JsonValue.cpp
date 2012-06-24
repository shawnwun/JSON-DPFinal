#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include "JsonValue.h"

using namespace std;

ostream& operator<< (ostream& os, JsonValue* v) {
    
    v->print(os, 1);
    return os;
}

void JsonValue::addLeaf(JsonValue* v) {}
JsonValue::JsonValue() { _type = NullType; };
JsonValue::JsonValue(int i) : _value(i) { _type = IntType; }
JsonValue::JsonValue(double d) : _value(d) { _type = DoubleType; }
JsonValue::JsonValue(bool b) : _value(b) { _type = BoolType; }
JsonValue::JsonValue(string &s) : _value(s) { _type = StringType; }
JsonValue::JsonValue(JsonArray *arr) : _value(arr) {
    cout << "JsonValue(arr): " << endl;
    _type = ArrayType;
}
JsonValue::JsonValue(JsonObject *obj) : _value(obj) {
    cout << "JsonValue(obj): " << endl;
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
//ValueType JsonValue::getType() { return _type; }
void JsonValue::print(ostream &os, int level) {
    switch (_type) {
    case JsonValue::IntType:
        os << _value._int;
        break;
    case JsonValue::DoubleType:
        os << _value._double;
        break;
    case JsonValue::StringType:
        os << _value._string;
        break;
    case JsonValue::BoolType:
        os << (_value._bool ? "true" : "false");
        break;
    case JsonValue::NullType:
        os << "null";
        break;
    default:
        // shouldn't reach here
        break;
    }
}


JsonValue::_JsonValue::_JsonValue() {}
JsonValue::_JsonValue::_JsonValue(int i) : _int(i) {
    cout << "_JsonValue(int): " << i << endl;
}
JsonValue::_JsonValue::_JsonValue(double d) : _double(d) {
    cout << "_JsonValue(double): " << d << endl;
}
JsonValue::_JsonValue::_JsonValue(bool b) : _bool(b) {
    cout << "_JsonValue(bool): " << b << endl;
}
JsonValue::_JsonValue::_JsonValue(string &str) {
    cout << "_JsonValue(char*): " << str << endl;
    _string = new char[str.size() + 1];
    strcpy(_string, str.c_str());            
}
//JsonValue::_JsonValue::_JsonValue(JsonArray *arr) : _array(arr) {
//    cout << "_JsonValue(arr): " << endl;
//}
JsonValue::_JsonValue::_JsonValue(JsonArray *arr) {
    cout << "_JsonValue(arr): " << endl;
    _array = new JsonArray(*arr);
}

//JsonValue::_JsonValue::_JsonValue(JsonObject *obj) : _object(obj) {
//    cout << "_JsonValue(obj): " << endl;
//}
JsonValue::_JsonValue::_JsonValue(JsonObject *obj) {
    cout << "_JsonValue(obj): " << endl;
    _object = new JsonObject(*obj);
}

/** Pair */
Pair::Pair(string &key, JsonValue *value)
    : _key(key), _value(value) {
}

string& Pair::getKey() { return _key; }
JsonValue* Pair::getValue() { return _value; }
void Pair::print(ostream &os, int level) {
    int width = level * 4;
    os << setw(width) << "" << _key << ": ";
    _value->print(os, level+1);
}


/** JsonObject */
JsonObject::JsonObject() {}
JsonObject::JsonObject(const JsonObject &rhs) {
    _jsonobj = rhs._jsonobj;
}
//JsonObject(map<string, JsonValue*>& ) {};
//JsonObject(const JsonObject& rhs) {};

void JsonObject::addLeaf(JsonValue* v) {
    Pair *p = (Pair *) v;
    _jsonobj.insert(make_pair(p->getKey(), p->getValue()));
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
JsonObject* JsonObject::getJsonObject(const string &key) {
    JSON_OBJECT::const_iterator it = _jsonobj.find(key);
    if (it != _jsonobj.end()) {
        return it->second->asJsonObject();
    } else {  // TODO: throw exception?
        cout << "no key: " << key << endl;
        return new JsonObject();
    }
}

void JsonObject::print(ostream &os, int level) {
    size_t size = _jsonobj.size();
    int i;
    JSON_OBJECT::const_iterator it;
    /*
    os << "{" << endl;
    for (it = _jsonobj.begin(), i = 0; i < size-1; ++it, ++i) {
        os << setw(4) << "" 
           << it->first << ": " << it->second << ", " << endl;// << it->second;
    }
    os << setw(4) << "" << it->first << ": " << it->second << endl;
    os << "}";
    */
    int width = level * 4;
    os << "{" << endl;
    for (it = _jsonobj.begin(), i = 0; i < size-1; ++it, ++i) {
        os << setw(width) << "" << it->first << ": ";
        it->second->print(os, level+1);
        os << ", " << endl;// << it->second;
    }
    os << setw(width) << "" << it->first << ": ";
    it->second->print(os, level+1);

    width = (level-1) * 4;
    os << endl << setw(width) << "" << "}";
}


/** JsonArray */
JsonArray::JsonArray() {}
JsonArray::JsonArray(const JsonArray &rhs) {
    _jsonarr = rhs._jsonarr;
}
// JsonArray(const JsonArray& rhs) {};

void JsonArray::addLeaf(JsonValue* v) {
    _jsonarr.push_back(v);
}

void JsonArray::print(ostream &os, int level) {
    vector<JsonValue*>::const_iterator it;
    int width = level * 4;
    os << "[" << endl;
    for (it = _jsonarr.begin(); it != _jsonarr.end()-1; ++it) {
        os << setw(width) << "";
        (*it)->print(os, level+1);
        os << ", " << endl;
    }
    os << setw(width) << "";
    (*it)->print(os, level+1);

    width = (level-1) * 4;
    os << endl << setw(width) << "" << "]";
}

