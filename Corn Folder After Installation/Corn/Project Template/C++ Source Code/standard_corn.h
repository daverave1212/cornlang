// THIS ONE
#ifndef STANDARD_CORN_H_INCLUDED
#define STANDARD_CORN_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>

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

string toString(int i){
    stringstream ss;
    ss << i;
    return ss.str();}

string toString(bool i){
    if(i == true) return "true";
	return "false";}

string toString(string s){
    return s;}

string toString(float i){
    stringstream ss;
    ss << i;
    return ss.str();}

string toString(char i){
    stringstream ss;
    ss << i;
    return ss.str();}

string toString(Object* o){
    cout << "OYdasda";
    if(o == NULL){
		cout<<"NULLm8    ";
		return "NULL";}
	cout<< "Not NUll    ";
    return o->asString();}

template <class T> string toString(T t){
    return "unknown";}

//-------------------------------- Random ---------------------------------

int randomInt(int int1, int int2){
	return (rand() % int2) + int1;}

float randomFloat(float a, int b){
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;}



//-------------------------------- ARRAY CLASS ---------------------------------

template <class T> class Array : public Object{public:

    T t;
    vector<T> v;
    int length = 0;
    string type = "Array";

    string asString(){
        string returnedString = "";
        for(int i = 0; i<length; i++){
			//cout<<typeOf(v[i]);
			//cout<<endl;
            returnedString += toString(v[i]) + " ";
			cout<<" returned string = " << returnedString << endl;}
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

	void shuffle(){
		for(int i = 0; i<length; i++){
			T auxT = v[i];
			int shuffleIndex = randomInt(0, length-1);
			v[i] = v[shuffleIndex];
			v[shuffleIndex] = auxT;
		}
	}

	};
template <class T> class Matrix : public Object{public:

	int nRows = 0;
	int nCols = 0;
	Array<Array<T>* >* matrix;
	T t;

	Matrix(){}
	Matrix(int r, int c){
		nRows = r;
		nCols = c;
		matrix = new Array< Array<T> >(r);
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


//-------------------------------- ARRAYS AND STRINGS elemmm ---------------------------------
template <class T> T& elem(Array<T>* a, int index){
    return a->v[index - 1];}

template <class T> Array<T>* elem(Matrix<T>* m, int index){
	return m->matrix->at(index);}

char& elem(string &s, int index){
    return s[index - 1];}

//-------------------------------- String API / Some Array API --------------------------------

int length(string s){
	return s.length();}

template <class T> int length(Array<T>* a){
	return a->length;}



bool contains(string s, char chr){
	for(int i = 0; i<s.length(); i++){
		if(s[i] == chr) return true;
	}
	return false;}
	
bool contains(string s, string c){
	if (s.find(c) != string::npos) {
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
	if(wordLength > 0 && s.substr(wordStartPos, wordLength).length() > 0){
		returnedArray->push( s.substr(wordStartPos, wordLength) );
	}
	return returnedArray;}

string substring(string s, int startIndex, int len){
	return s.substr(startIndex-1, len);}

string substringUntilPosition(string s, int endIndex){
	return s.substr(0, endIndex);}
	
string substringUntil(string s, int endIndex){
	return s.substr(0, endIndex);}

string substringFromPosition(string s, int startIndex){
	return s.substr(startIndex - 1, s.length() - startIndex + 1);}

string substringFrom(string s, int startIndex){
	return s.substr(startIndex - 1, s.length() - startIndex + 1);}

//-------------------------------- Print --------------------------------
class CornStream{public:

	friend CornStream &operator<<(CornStream& cornStream, char* s);
	friend CornStream &operator<<(CornStream& cornStream, string s);
	friend CornStream &operator<<(CornStream& cornStream, int s);
	friend CornStream &operator<<(CornStream& cornStream, float s);
	//friend CornStream &operator<<(CornStream& cornStream, bool s);
	friend CornStream &operator<<(CornStream& cornStream, char s);
	template <class T> friend CornStream &operator<<(CornStream& cornStream, Array<T>* a);
	template <class T> friend CornStream &operator<<(CornStream& cornStream, Matrix<T>* a);
	
	friend CornStream &operator>>(CornStream& cornStream, char* s);
	friend CornStream &operator>>(CornStream& cornStream, string &s);
	friend CornStream &operator>>(CornStream& cornStream, int &s);
	friend CornStream &operator>>(CornStream& cornStream, float &s);
	//friend CornStream &operator<<(CornStream& cornStream, bool s);
	friend CornStream &operator>>(CornStream& cornStream, char &s);

};
//  wait

void wait(int milliseconds){
	Sleep(milliseconds);}
	
//	getch
void pause(){
	cin.ignore();}

//	Read

/*CornStream &operator>>(CornStream& cornStream, char* s){
	getline(cin, s);
	return cornStream;}
*/

CornStream &operator>>(CornStream& cornStream, string& s){
	//getline(cin, s);
	cin>>s;
	return cornStream;}


CornStream &operator>>(CornStream& cornStream, int& s){
	cin>>s;
	return cornStream;}

CornStream &operator>>(CornStream& cornStream, float& s){
	cin>>s;
	return cornStream;}

CornStream &operator>>(CornStream& cornStream, char& s){
	cin>>s;
	return cornStream;}


//	Print
CornStream &operator<<(CornStream& cornStream, char* s){
	cout<<s;
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, bool s){
	if(s) cout<<"true";
	else cout<<"false";
	return cornStream;}
	

CornStream &operator<<(CornStream& cornStream, string s){
	cout<<s;
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, int s){
	cout<<s;
	return cornStream;}

CornStream &operator<<(CornStream& cornStream, float s){
	cout<<s;
	return cornStream;}

/*CornStream &operator<<(CornStream& cornStream, bool s){
	if(s == true) cout<<"true";
	else cout<<"false";
	return cornStream;}
	*/

CornStream &operator<<(CornStream& cornStream, char s){
	cout<<s;
	return cornStream;}


template <class T> CornStream &operator<<(CornStream& cornStream, Array<T>* a){
	cout<<"Printing for array\n";
	cout<<a->asString();
	return cornStream;}

template <class T> CornStream &operator<<(CornStream& cornStream, Matrix<T>* a){
	cout<<a->asString();
	return cornStream;}

//-------------------------------- Conversion Functions --------------------------------

int toInt(string s){
	return atoi(s.c_str());}

int toInt(float f){
	return static_cast<int>(f);}

int charCode(char c){
	return (int)c;}
	
/*int toInt(bool b){
	if(b) return 1;
	else return 0;}
*/

int boolToInt(bool b){
	if(b) return 1;
	else return 0;
}

float toFloat(string s){
	return atof(s.c_str());}

float toFloat(int i){
	return (float)i;}


bool toBool(string s){
	if(s == "true") return true;
	return false;}

bool toBool(char c){
	if(c == 't' || c == 1) return true;
	return false;
}
	
//-------------------------------- File Class --------------------------------

class File{public:

	static string readFile(string path){
		ifstream t(path.c_str());
		if(!t){
			cout<<"ERROR: File at "<<path<<" failed read.\n";
			return "";}
		string returnedString((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
		t.close();
		return returnedString;}

	static void writeFile(string stringToWrite, string path){
		ofstream t(path.c_str());
		if(!t){
			cout<<"ERROR: Failed to write file "<<path<<".\n";
			return;}
		t<<stringToWrite;
		t.close();}

};


#endif // STANDARD_CORN_H_INCLUDED
