#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "JsonParser.tab.c"
#include "ConcreteBuilder.h"
#include "PrintImp.h"
using namespace std;

int main(void) {
    ifstream jsonFile("json.js");

    stringstream ss;
    ss << jsonFile.rdbuf();

    string jsonStr(ss.str());

    // Config print function
    //JsonValue::ConfigImp(new DefaultPrintImp());
    JsonValue::ConfigImp(new PrettyPrintImp(2));

    JsonObject* data = (JsonObject*) callParser(new ConcreteBuilder(), jsonStr);
    if (data) {
        cout << "Correct JSON" << endl;
        cout << "==============================" << endl;
        cout << data << endl;
        //data->getJsonObject("glossary")->print();
    }
    else
        cout << "Incorrect JSON" << endl;

    return 0;
}
