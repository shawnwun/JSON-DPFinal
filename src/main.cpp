#include <iostream>
#include "JSONObject.h"
#include "Object.h"
#include "JSONReader.h"
#include "JSONWritter.h"

using namespace std;

void testcase1(){

    string testcase = "[\"a\",1,\[\"Spain\",\"Italy\",25.3\],\{\"name\":\"Lionel Messi\",\"age\":1 \}]"
    JSONReader jReader;
    JSONArray* jArray = jReader.read(testcase1);
    
    jArray.showPrettify();
    jArray.put(1);
    jArray.put(0.46);
    jArray.put("King of the world");
    jArray.showPrettify();
    
    JSONWritter jWritter;
    string result = jWritter(jArray);
    cout << result << endl;
}

void testcase2(){
    /* Specify your test case here */
}

void testcase3(){
    /* Specify your test case here */
}


int main(int argc, char** argv){
    if(argc!=2){
	cout << "Usage: ./testcase <TestCase_ID>" << endl;
	exit(-1);
    }

    int caseID = int(argv[1]);

    switch(caseID){
	case 1: testcase1() break;
	case 2: testcase2() break;
	case 3: testcase3() break;
	/* Add new case here */

	default:
	    cout << "No Matching testcases, exit!" << endl;
	    break;
    }

    return 0;
}

