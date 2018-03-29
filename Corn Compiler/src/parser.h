#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include "object_finder.h"

#define print std::cout<<
#define read  std::cin>>

#define newEmptyStringVector std::vector<std::string>(0)
#define StringMatrix std::vector<std::vector<std::string>>

void printArray(std::vector<std::string> v){
    for(int i = 0; i<v.size(); i++){
        std::cout<<v[i]<< " ";}
    std::cout<<"\n";
}

inline bool isSpaceOrTab(char c){
    if(c == ' ' || c == '\t') return true;
    else return false;}

std::string singleOperatorCharacters = "()[]{};,.";
inline bool isSingleOperator(char c){
    if(singleOperatorCharacters.find(c) != std::string::npos){
        return true;}
    return false;
}

std::string doubleOperatorCharacters = "!%&*|=-+<>";
inline bool isDoubleOperator(char c){
    if(doubleOperatorCharacters.find(c) != std::string::npos){
        return true;}
    else return false;
}

void splitStringIntoWords(std::string &s, std::vector<std::string>& v){
	print "Splitting string into words...\n";

    std::string currentWord = "";
    bool lastCharacterWasDoubleOperator   = false;    // ONLY FOR DOUBLE OPERATORS
    bool lastCharacterWasSpace      = false;
    bool lastCharacterWasLetter     = false;

    for(int i = 0; i<s.length(); i++){
        char currentLetter = s[i];

        if( isSpaceOrTab(currentLetter) ){ //..."  "...
            if(currentWord.length() > 0){
				print "Found tab or space. Pushing word: ";
				print currentWord;
				print "\n";
                v.push_back(currentWord);
                currentWord = "";}
            lastCharacterWasDoubleOperator = false;
            lastCharacterWasSpace = true;}

        else if( isSingleOperator(currentLetter)){ //...(...
            if(currentWord.length() > 0){
				print "Found single operator. Pushing word: ";
				print currentWord;
				print "\n";
                v.push_back(currentWord);}
            currentWord = currentLetter;
			print "Now pushing operator: ";
			print currentWord;
			print "\n";
            v.push_back(currentWord);
            currentWord = "";
            lastCharacterWasSpace = false;
            lastCharacterWasDoubleOperator = false;}

        else if( isDoubleOperator(currentLetter) ){ //...+ or ...+=...
            lastCharacterWasSpace   = false;
            lastCharacterWasLetter  = false;
            if( lastCharacterWasDoubleOperator ){
                currentWord += currentLetter;
				print "Found double operator. Pushing it: ";
				print currentWord;
				print "\n";
                v.push_back(currentWord);
                currentWord = "";
                lastCharacterWasDoubleOperator = false;}
            else if( lastCharacterWasDoubleOperator == false ){
                if(currentWord.length() > 0){
					print "Found a (possible double) operator. Pushing word behind: ";
					print currentWord;
					print "\n";
                    v.push_back(currentWord);}
                lastCharacterWasDoubleOperator = true;
                currentWord = "";
                currentWord += currentLetter;}}

        else { //...aLetter...
            lastCharacterWasLetter  = true;
            lastCharacterWasSpace   = false;
            if(lastCharacterWasDoubleOperator){
				print "Found a single-double-operator. Pushing it: ";
				print currentWord;
				print "\n";
                v.push_back(currentWord);
                currentWord = "";
                lastCharacterWasDoubleOperator = false;}
            currentWord += currentLetter;}
		if(i == s.length() - 1){
			if(currentWord.length() > 0){
				v.push_back(currentWord);
				currentWord = "";
			}
			lastCharacterWasSpace = true;
			lastCharacterWasDoubleOperator = false;
			lastCharacterWasLetter = true;
		}
    }
}

void readFileIntoWords(std::string &pathToFile, StringMatrix &inputWords){
    std::ifstream readFile(pathToFile);
    std::string currentLine = "";

    int currentLineIndex = 0;

    while(std::getline(readFile, currentLine)){
        print "pushing line n " << currentLineIndex << "...\n";
        inputWords.push_back(newEmptyStringVector);
        print "pushed. splitting <[" << currentLine<< "]> into words\n";
        splitStringIntoWords(currentLine, inputWords[currentLineIndex]);
        print "split\n";
        currentLineIndex++;}
}

void cornToCPP(StringMatrix &in, StringMatrix &out){
	std::cout<<"Transforming code into cpp\n";
	std::cout<<"Length of in: "<<in.size()<<"\n";
	out.reserve(in.size());	//this doesn't do anything, it just reserves so it runs faster!
	for(int i = 0; i<in.size(); i++){
		out.push_back(newEmptyStringVector);
		out[i].reserve(in[i].size()); //same here. if we remove the 2 lines, it works still
		for(int j = 0; j<in[i].size(); j++){
			out[i].push_back(in[i][j]);
		}
	}
}

std::string parseCode(std::string pathToFile){

    StringMatrix inputWords(0);
    StringMatrix outputWords(0);

    readFileIntoWords(pathToFile, inputWords);
	print "input words size: ";
	print inputWords.size();
	print "\n";

    cornToCPP(inputWords, outputWords);

	print "output words size: ";
	print outputWords.size();
	print "\n";

	std::string returnedString = "";
	for(int i = 0; i<outputWords.size(); i++){
		for(int j = 0; j<outputWords[i].size(); j++){
			returnedString += outputWords[i][j] + " ";
			std::cout<<"Word: " << outputWords[i][j] << "\n";
		}
		returnedString += "\n";
	}

    return returnedString;
}



/*
    Input:
        Read file line by line
        Each Line:
            line -> words
            code[currentLine].push words
            currentLine++;

*/




#endif // PARSER_H_INCLUDED
