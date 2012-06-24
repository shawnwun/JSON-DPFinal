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

int main(int argc, char** argv) {
    if(argc!=2){
	cout << "Usage: ./main json_file" << endl;
	exit(-1);
    }
    string filename = argv[1];
    ifstream jsonFile(filename.c_str());

    stringstream ss;
    ss << jsonFile.rdbuf();

    string jsonStr(ss.str());

    // Config print function
    //JsonValue::ConfigImp(new DefaultPrintImp());
    JsonValue::ConfigImp(new PrettyPrintImp(4));

    JsonValue* data = callParser(new ConcreteBuilder(), jsonStr);
    
    if(data){
	cout << "Correct JSON" << endl;
        cout << "==============================" << endl;
        cout << data << endl;
        cout << data->getObjectByKey("glossary") << endl;
        cout << data->getObjectByKey("alan") << endl;
        cout << data->getObjectByIndex(1) << endl;
	cout << endl;
    } 

    return 0;
}
