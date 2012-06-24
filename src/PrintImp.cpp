#include "PrintImp.h"

void DefaultPrintImp::print(ostream& os, JsonValue* jv, int level) const{
    jv->print(os,level);
}
void DefaultPrintImp::print(ostream& os, Pair* jv, int level) const{
    os << jv->getKey() << ":";
    jv->getValue()->print(os, level+1);
}
void DefaultPrintImp::print(ostream& os, JsonObject* jv, int level) const{
    size_t size = jv->getObjectMapping().size();
    int i;
    map<string, JsonValue*>::const_iterator it;
    map<string, JsonValue*> mymap = jv->getObjectMapping();   
 
    os << "{";
    for (it = mymap.begin(), i = 0; i < size-1; ++it, ++i) {
        os << it->first << ":";
        it->second->print(os, level+1);
        os << ", ";// << it->second;
    }
    os << it->first << ":";
    it->second->print(os, level+1);
    os << "}";
}
void DefaultPrintImp::print(ostream& os, JsonArray* jv, int level) const{
    vector<JsonValue*>::const_iterator it;
    vector<JsonValue*> myvec = jv->getObjectList();    
    size_t size = jv->getObjectList().size();
    int i;
    os << "[";
    for (it = myvec.begin(), i=0; i<size-1; ++it,++i) {
        (*it)->print(os, level+1);
        os << ", ";
    }
    (*it)->print(os, level+1);
    os << "]";
}

void PrettyPrintImp::print(ostream& os, JsonValue* jv, int level) const{
    jv->print(os,level);
}
void PrettyPrintImp::print(ostream& os, Pair* jv, int level) const{
    int width = level * _sep;
    os << setw(width) << "" << jv->getKey() << ": ";
    jv->getValue()->print(os, level+1);
}
void PrettyPrintImp::print(ostream& os, JsonObject* jv, int level) const{
    size_t size = jv->getObjectMapping().size();
    int i;
    map<string, JsonValue*>::const_iterator it;
    map<string, JsonValue*> mymap = jv->getObjectMapping();   
 
    int width = level * _sep;
    os << "{" << endl;
    for (it = mymap.begin(), i = 0; i < size-1; ++it, ++i) {
        os << setw(width) << "" << it->first << ": ";
        it->second->print(os, level+1);
        os << ", " << endl;// << it->second;
    }
    os << setw(width) << "" << it->first << ": ";
    it->second->print(os, level+1);

    width = (level-1) * _sep;
    os << endl << setw(width) << "" << "}";
}
void PrettyPrintImp::print(ostream& os, JsonArray* jv, int level) const{
    vector<JsonValue*>::const_iterator it;
    vector<JsonValue*> myvec = jv->getObjectList();    

    int width = level * _sep;
    size_t size = jv->getObjectList().size();
    int i;
    os << "[" << endl;
    for (it = myvec.begin(), i=0; i<size-1; ++it,++i) {
	os << setw(width) << "";
        (*it)->print(os, level+1);
        os << ", " << endl;
    }
    os << setw(width) << "";
    (*it)->print(os, level+1);

    width = (level-1) * _sep;
    os << endl << setw(width) << "" << "]";
}


