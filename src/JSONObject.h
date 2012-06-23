#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <map>
#include <vector>
#include "JsonValue.h"


class JsonObject : public JsonValue {
public:
    JsonObject();
    //JsonObject(map<String*, JsonValue*>& );

    virtual void addLeaf(JsonValue* v) {
        Pair *jsonPair = (Pair *) v;
        _jsonobj.insert(jsonPair->asPair());
    }
    
private:
    map<String*, JsonValue*> _jsonobj;
};


class JsonArray : public JsonValue {
public:
    JsonArray();
    JsonArray(vector<JsonValue*>& );

    virtual void addLeaf(JsonValue* v) {
        _jsonarr.push_back(v);
    }

private:
    vector<JsonValue*> _jsonarr;
};


#endif

