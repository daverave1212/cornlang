//Version 0.07

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include "object_finder.h"
#include "quote_characters.h"
#include "map_words_definitions.h"

#define print std::cout<<
#define read  std::cin>>

#define newEmptyStringVector std::vector<std::string>(0)
#define StringMatrix std::vector<std::vector<std::string>>

#define ENDFOR }
#define FirstLetterIsOperator(x) ( x[0] >= 33 && x[0] <= 47 ) || ( x[0] >= 58 && x[0] <= 64 ) || ( x[0] >= 91 && x[0] <= 94 ) || ( x[0] == 96 ) || ( x[0] >= 193 && x[0] <= 196 )
#define FirstLetterIsNumber(x) ( x[0] >= 48 && x[0] <= 57 )



std::string getPreviousWord(int currentRowIndex, int currentColIndex, StringMatrix &words){
	int previousRowIndex = currentRowIndex;
	int previousColIndex = currentColIndex - 1;
	while(previousColIndex < 0){
		previousRowIndex--;
		if(previousColIndex < 0){
			return "NOPREVIOUSWORD";
		}
		previousColIndex = words[previousRowIndex].size() - 1;
	}
	return words[previousRowIndex][previousColIndex];}

#define previousWord getPreviousWord(i, j, inputWords)


#define FirstLetterOf(x) x[0]

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

std::string operatorCharacters = "()[]{};,.!%&*|=-+<>";
inline bool isCharOperator(char c){
    if(operatorCharacters.find(c) != std::string::npos){
        return true;}
    else return false;}

inline bool isStringOperator(std::string s){
	if(s.length() == 0 || s.length() > 2){
		return false;}
	if(isCharOperator(s[0])){
		return true;}
	else return false;
}

inline bool isQuote(char c){
	if(c == QUOTECHARACTER){
		return true;}
	else return false;
}

void splitStringIntoWords(std::string &s, std::vector<std::string>& v){
	print "Splitting string into words...\n";

    std::string currentWord = "";
    bool lastCharacterWasDoubleOperator   = false;    // ONLY FOR DOUBLE OPERATORS
	bool isProcessingString = false;


    for(int i = 0; i<s.length(); i++){
        char currentLetter = s[i];

		if( isQuote(currentLetter) ){
			print "Found a quote----\n";
			if( !isProcessingString ){
				if(currentWord.length() > 0){
					print "Found a quote. Pushing word: ";
					print currentWord;
					print "\n";
					v.push_back(currentWord);
					currentWord = "";}
				currentWord = QUOTESTRING;
				isProcessingString = true;
				lastCharacterWasDoubleOperator = false;}
			else{
				currentWord += currentLetter;
				print "Ended a string. Pushing it as a whole word: ";
				print currentWord;
				print "\n";
				v.push_back(currentWord);
				currentWord = "";
				isProcessingString = false;}}

		else if(isProcessingString){
			currentWord += currentLetter;
		}

        else if( isSpaceOrTab(currentLetter) ){ //..."  "...
            if(currentWord.length() > 0){
				print "Found tab or space. Pushing word: ";
				print currentWord;
				print "\n";
                v.push_back(currentWord);
                currentWord = "";}
            lastCharacterWasDoubleOperator = false;}

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
            lastCharacterWasDoubleOperator = false;}

        else if( isDoubleOperator(currentLetter) ){ //...+ or ...+=...
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
				currentWord = "";}
			lastCharacterWasDoubleOperator = false;
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
        currentLineIndex++;}}

std::string parseCode(std::string pathToFile, Map<int>& map){

    StringMatrix in(0);
    StringMatrix out(0);

    readFileIntoWords(pathToFile, in);
	print "input words size: ";
	print in.size();
	print "\n";

	/* 			cornToCPP(inputWords, outputWords, map){ */
    std::cout<<"Transforming code into cpp\n";
	std::cout<<"Length of in: "<<in.size()<<"\n";

	bool isWritingString = false;

	out.reserve(in.size());	//this doesn't do anything, it just reserves so it runs faster!

	bool nextWordIsImportPath = false;

	for(int i = 0; i<in.size(); i++){
		out.push_back(newEmptyStringVector);
		out[i].reserve(in[i].size()); //same here. if we remove the 2 lines, it works still
		for(int j = 0; j<in[i].size(); j++){
			std::string inputWord = in[i][j];
			std::string outputWord = "";

			//CODE FOR INTERPRETING WORDS IS HERE

			if(nextWordIsImportPath){	// "standard.corn"
				nextWordIsImportPath = false;
				inputWord = inputWord.substr(1, inputWord.length() - 2);
				outputWord = parseCode(inputWord, map);}
			else if(isStringOperator(inputWord)){	// + - = \ ...
				switch(inputWord){
					case "->":
						outputWord = ".";
						break;}}
			else{	//aWord...
				int currentWordAsInt = map.getData(inputWord);
				switch(currentWordAsInt){
					case NOT_FOUND:
						outputWord = inputWord;
						break;
					case IMPORT:
						outputWord = "\n";
						nextWordIsImportPath = true;
						break;

				}
			}



			//CODE FOR INTERPRETING WORDS IS HERE
			out[i].push_back(outputWord);
		}//end for
	}
    /* cornToCPP(inputWords, outputWords, map){ */

	print "output words size: ";
	print out.size();
	print "\n";

	std::string returnedString = "";
	for(int i = 0; i<out.size(); i++){
		for(int j = 0; j<out[i].size(); j++){
			returnedString += out[i][j] + " ";
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
