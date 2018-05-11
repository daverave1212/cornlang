#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Object{public:

    virtual string asString(){return "Object";}
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
    return o->asString();}

template <class T> string toString(T t){
    return "unknown";}

//-------------------------------- ARRAY CLASS ---------------------------------

template <class T> class Array : public Object{public:

    T t;
    vector<T> v;
    int length = 0;
    string type = "Array";

    string asString(){
        string returnedString = "";
        cout<<"Definitely here.";
        for(int i = 0; i<length; i++){
            returnedString += toString(v[i]) + " ";}
        return returnedString;}

    Array(){}

    Array(int nElements){
        v = vector<T>(nElements);
        length = nElements;}

	T at(int index){		//change to index - 1
		return v[index];}

    void push(T t){
        length++;
        v.push_back(t);}

	void addElement(){
		length++;
		v.push_back(t);}

	T pop(){
		T temp = v[length - 1];
		v.pop_back();
		length--;
		return temp;}

	int getLength(){
		return length;}

	};
template <class T> class Matrix : public Object{public:

	int nRows = 0;
	int nCols = 0;
	Array<Array<T>*>* matrix;
	T t;

	Matrix(){}
	Matrix(int r, int c){
		nRows = r;
		nCols = c;
		matrix = new Array<Array<T>>(r);
		for(int i = 0; i<r; i++){
			matrix->v[i] = new Array<T>(c);
		}
	}

	string asString(){
		string returnedString = "";
		for(int i = 0; i<nRows; i++){
			returnedString = matrix->at(i)->asString() + "/n";}
		return returnedString;}

	void addColumn(){
		for(int i = 0; i<nRows; i++){
			matrix->at(i)->push(t);}
		nCols++;}

	void addRow(){
		matrix->push(new Array<T>(nCols));
		nRows++;
	}



};


//-------------------------------- ARRAYS AND STRINGS ---------------------------------
template <class T> T elem(Array<T>* a, int index){
    return a->v[index - 1];}

template <class T> Array<T>* elem(Matrix<T>* m, int index){
	return m->matrix->at(index);}

char elem(string s, int index){
    return s[index - 1];}

//-------------------------------- String API / Some Array API --------------------------------

int length(string s){
	return s.length();}

template <class T> int length(Array<T>* a){
	return a->length;}

bool contains(string s, string c){
	if (size_t index = s.find(c)) {
		return true;}
	return false;}

bool contains(string s, char chr){
	string c = chr + "";
	if (size_t index = s.find(c)) {
		return true;}
	return false;}

int positionOf(string s, string c){
	if (size_t index = s.find(c)) {
		return index + 1;}
	return 0;}

int positionOf(string s, char chr){
	string c = chr + "";
	if (size_t index = s.find(c)) {
		return index + 1;}
	return 0;}

Array<string>* split(string s){
	string delimiters = " ";
	Array<string>* returnedArray = new Array<string>(0);
	int wordStartPos = 0;
	int wordLength = 0;
	for(int i = 0; i<s.length(); i++){
		if(contains(delimiters, s[i]) != 0){
			returnedArray->push( s.substr(wordStartPos, wordLength) );
			wordStartPos = i+1;
			wordLength = 0;}
		else{
			wordLength++;}}
	return returnedArray;}

Array<string>* split(string s, string delimiters){
	Array<string>* returnedArray = new Array<string>(0);
	int wordStartPos = 0;
	int wordLength = 0;
	for(int i = 0; i<s.length(); i++){
		if(contains(delimiters, s[i]) != 0){
			returnedArray->push( s.substr(wordStartPos, wordLength) );
			wordStartPos = i+1;
			wordLength = 0;}
		else{
			wordLength++;}}
	return returnedArray;}

string substring(string s, int startIndex, int len){
	return s.substr(startIndex-1, len);}

string substringUntilPosition(string s, int endIndex){
	return s.substr(0, endIndex - 1);}

string substringFromPosition(string s, int startIndex){
	return s.substr(startIndex - 1, s.length() - startIndex + 1);
}

//-------------------------------- Print --------------------------------
class CornStream{public:

	friend CornStream &operator<<(CornStream& cornStream, string s);
	friend CornStream &operator<<(CornStream& cornStream, int s);
	friend CornStream &operator<<(CornStream& cornStream, float s);
	friend CornStream &operator<<(CornStream& cornStream, bool s);
	friend CornStream &operator<<(CornStream& cornStream, char s);
	template <class T> friend CornStream &operator<<(CornStream& cornStream, Array<T>* a);
	template <class T> friend CornStream &operator<<(CornStream& cornStream, Matrix<T>* a);

};

CornStream &operator<<(CornStream& cornStream, string s){
	cout<<s;
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, int s){
	cout<<s;
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, float s){
	cout<<s;
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, bool s){
	if(s == true) cout<<"true";
	else cout<<<"false";
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, char s){
	cout<<s;
	return cornStream;}


template <class T> CornStream &operator<<(CornStream& cornStream, Array<T>* a){
	cout<<a->asString();
	return cornStream;}

template <class T> CornStream &operator<<(CornStream& cornStream, Matrix<T>* a){
	cout<<a->asString();
	return cornStream;}

//-------------------------------- Conversion Functions --------------------------------

int toInt(string s){
	return atoi(s.c_str());}

int toInt(float f){
	return (int)f;}

int toInt(char c){
	return (int)c;}

float toFloat(string s){
	return atof(s.c_str());}

float toFloat(int i){
	return (float)i;}




//-------------------------------- Global Vars --------------------------------


class O : public Object{public:
	string type = "O";
};

int main()
{
    CornStream coro;

    Array<string>* a = new Array<string>(0);
    a->push("a");
    a->push("b");
    a->push("c");
    a->push("d");
    string s = "abcdefghij";
    coro<<a;
    return 0;

    //cout<<a->v[2];
    //cout<<a->asString();

    Array<O*>* b = new Array<O*>(0);
    b->push(new O());
    b->push(new O());
    b->push(new O());
    b->push(new O());
    b->push(new O());
    //cout<<toString(b->v[2]);
    //cout<<b->asString();

    Array<int>* o = new Array<int>(23);
	o->push(123);
	cout<< o->type;

    return 0;
}
