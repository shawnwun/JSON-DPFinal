#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "JsonParser.tab.c"
#include "ConcreteBuilder.h"
using namespace std;

int main(void) {
    ifstream jsonFile("json.js");

    stringstream ss;
    ss << jsonFile.rdbuf();

    string jsonStr(ss.str());

    JsonObject* data = (JsonObject*) callParser(new ConcreteBuilder(), jsonStr);
    if (data) {
        cout << "Correct JSON" << endl;
        cout << "==============================" << endl;
        cout << data;
        //data->getJsonObject("glossary")->print();
    }
    else
        cout << "Incorrect JSON" << endl;


    system("pause");
    return 0;
}
