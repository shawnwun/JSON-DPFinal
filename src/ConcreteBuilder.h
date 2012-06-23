#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>
#include <string>
#include "JsonBuilder.h"
using namespace std;

class ConcreteBuilder : public JsonBuilder {
	public:
		// Encounter JSON Value (Leaf Node)
		virtual JsonValue* meetString(std::string str){
			cout << "Meet String " << str << endl;
			return 0;
		}
		virtual JsonValue* meetNumber(double num){
			cout << "Meet Number " << num << endl;
			return 0;
		}
		virtual JsonValue* meetBool(bool val){
			cout << "Meet BOOL " << val << endl;
			return 0;
		}
		virtual JsonValue* meetNULL(){
			cout << "Meet NULL " << endl;
			return 0;
		}
		virtual JsonValue* meetPair(JsonValue* key, JsonValue* value){
			cout << "Meet NewPair " << endl;
			return 0;
		}

		// Encounter JSON Map or Array (Composite Node)
		virtual JsonValue* meetMapBegin(){
			cout << "Meet MapBegin" << endl;
			return new JsonObject;
		}
		virtual JsonValue* meetArrayBegin(){
			cout << "Meet ArrayBegin" << endl;
			return new JsonValue;
		}
		virtual void mapMeetNewPair(JsonValue* map, JsonValue* pair){
			cout << "Meet MapPair" << endl;
		}
		virtual void arrayMeetNewElement(JsonValue* array, JsonValue* element){
			cout << "Meet Element" << endl;
		}
};

#endif
