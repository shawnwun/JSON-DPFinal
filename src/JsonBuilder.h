#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include <string>
#include "JsonValue.h"

class JsonBuilder{
	public:
		// Encounter JSON Value (Leaf Node)
		virtual JsonValue* meetString(std::string str) = 0;
		virtual JsonValue* meetNumber(double num) = 0;
		virtual JsonValue* meetBool(bool val) = 0;
		virtual JsonValue* meetNULL() = 0;
		virtual JsonValue* meetPair(JsonValue* key,JsonValue* value) = 0;

		// Encounter JSON Map or Array (Composite Node)
		virtual JsonValue* meetMapBegin() = 0;
		virtual JsonValue* meetArrayBegin() = 0;
		virtual void mapMeetNewPair(JsonValue* map, JsonValue* pair){
			map->addLeaf(pair);
		}
		virtual void arrayMeetNewElement(JsonValue* array, JsonValue* element){
			array->addLeaf(element);
		}
};

#endif
