#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "JsonParser.tab.c"
#include "ConcreteBuilder.h"
#include "PrintImp.h"
//#include "JsonValue.h"
//#include "JsonException.h"

using namespace std;

int main(void) {
    ifstream jsonFile("json.js");

    stringstream ss;
    ss << jsonFile.rdbuf();

    string jsonStr(ss.str());

    // Config print function
    //JsonValue::ConfigImp(new DefaultPrintImp());
    JsonValue::ConfigImp(new PrettyPrintImp(4));

    //JsonValue* data = callParser(new ConcreteBuilder(), jsonStr);
    JsonObject* data = (JsonObject*)callParser(new ConcreteBuilder(), jsonStr);
    
    if(data){
	cout << "Correct JSON" << endl;
        cout << "==============================" << endl;
        cout << data << endl;
        cout << data->getObjectByKey("glossary") << endl;
	cout << endl;
    } 

    return 0;
}
