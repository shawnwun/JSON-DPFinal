#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <map>
#include <vector>
#include "Object.h"

class JSONObject : public Object{
public:
    JSONObject(){}
    JSONObject(map<Object*,object*>* );
    
    


private:
    map<Object*,Object*>* _jsonobj;
};

class JSONArray : public Object{
public:
    JSONArray()}{}
    JSONArray(vector<Object*>* );

private:
    vector<Object*>* _jsonarr;
};


#endif

