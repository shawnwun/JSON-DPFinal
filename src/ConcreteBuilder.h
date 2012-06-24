#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>
#include <string>
#include "JsonBuilder.h"
//#include "JsonValue.h"
using namespace std;

class ConcreteBuilder : public JsonBuilder {
    public:
        // Encounter JSON Value (Leaf Node)
        virtual JsonValue* meetString(std::string str){
            //cout << "Meet String " << str << endl;
            return new JsonValue(str);
        }
        virtual JsonValue* meetNumber(double num) {
            //cout << "Meet Number " << num << endl;
            return new JsonValue(num);
        }
        virtual JsonValue* meetBool(bool val) {
            //cout << "Meet BOOL " << val << endl;
            return new JsonValue(val);
        }
        virtual JsonValue* meetNULL() {
            //cout << "Meet NULL " << endl;
            return new JsonValue();
        }
        virtual JsonValue* meetPair(JsonValue* key, JsonValue* value) {
            //cout << "Meet NewPair " << endl;
            string str = key->asString();
            return new Pair(str, value);
        }

        // Encounter JSON Map or Array (Composite Node)
        virtual JsonValue* meetMapBegin() {
            //cout << "Meet MapBegin" << endl;
            return new JsonObject;
        }
        virtual JsonValue* meetArrayBegin() {
            //cout << "Meet ArrayBegin" << endl;
            return new JsonArray;
        }
        virtual void mapMeetNewPair(JsonValue* aMap, JsonValue* aPair) {
            //cout << "Meet MapPair"
            //     << ((Pair*)aPair)->getKey() << endl;
            aMap->addLeaf(aPair);
        }
        virtual void arrayMeetNewElement(JsonValue* array, JsonValue* element) {
            //cout << "Meet Element" << endl;
            array->addLeaf(element);
        }
};

#endif
