#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "JsonParser.tab.c"
#include "ConcreteBuilder.h"
#include "PrintImp.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc!=4){
	cout << "Usage: ./main json_file [defult|pretty] line_sep" << endl;
	exit(-1);
    }
    string filename = argv[1];
    string printConfig = argv[2];
    int line_sep = atoi(argv[3]);
    
    ifstream jsonFile(filename.c_str());

    stringstream ss;
    ss << jsonFile.rdbuf();

    string jsonStr(ss.str());

    // Config print function
    if(printConfig=="default")
	JsonValue::ConfigImp(new DefaultPrintImp());
    else if(printConfig=="pretty")
	JsonValue::ConfigImp(new PrettyPrintImp(line_sep));

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

