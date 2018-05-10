#include <iostream>
#include <vector>

using namespace std;

class Object{public:

    virtual string toStr(){return "Object";}
    string type = "Object";

    };

//-------------------------------- TYPE OF ---------------------------------

string typeOf(Object* o){
    return o->type;}

string typeOf(int i){
    return "int";}

string typeOf(char c){
    return "char";}

string typeOf(bool b){
    return "bool";}

string typeOf(string s){
    return "string";}

string typeOf(float f){
    return "float";}

template <class T> string typeOf(T t){
    return "unknown";}
//-------------------------------- toString() ---------------------------------

string toString(string s){
    return s;}

string toString(int i){
    return "" + i;}

string toString(bool b){
    return "" + b;}

string toString(float f){
    return (int)f + "";}

string toString(char c){
    return "" + c;}

string toString(Object* o){
    cout << "OY";
    if(o == NULL) return "NULL";
    return o->toStr();}

template <class T> string toString(T t){
    cout<< "CRA";
    return "unknown";}

//-------------------------------- ARRAY CLASS ---------------------------------

template <class T> class Array : public Object{public:

    T t;
    vector<T> v;
    int length = 0;
    string type = "Array";

    string toStr(){
        string returnedString = "";
        cout<<"Definitely here.";
        for(int i = 0; i<length; i++){
            returnedString += toString(v[i]) + " ";}
        return returnedString;
    }

    Array(){}

    Array(int nElements){
        type = "Array";
        v = vector<T>(nElements);
        length = nElements;}

    void push(T t){
        length++;
        v.push_back(t);}

    };


//-------------------------------- ARRAYS AND STRINGS ---------------------------------
template <class T> T elem(Array<T>* a, int index){
    return a->v[index - 1];}

char elem(string s, int index){
    return s[index - 1];}

//-------------------------------- Global Vars --------------------------------


class O : public Object{public:};
int main()
{
    Array<string>* a = new Array<string>(0);
    a->push("a");
    a->push("b");
    a->push("c");
    a->push("d");
    string s = "abcdefghij";

    //cout<<a->v[2];
    //cout<<a->toStr();

    Array<O*>* b = new Array<O*>(0);
    b->push(new O());
    b->push(new O());
    b->push(new O());
    b->push(new O());
    b->push(new O());
    //cout<<toString(b->v[2]);
    //cout<<b->toStr();

    Object* o = new O();

    return 0;
}
