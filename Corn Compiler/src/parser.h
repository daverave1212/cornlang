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
#define LastWordOfInputLine in[i][nWordsInLine - 1]
#define LastWordOfOutputLine out[i][out[i].size() - 1]
#define code(x) map.getData(x)

#define check(x) else if(inputWord == x)

void printArray(std::vector<std::string> v){
	std::cout<<"\n";
	for( int i = 0; i<v.size(); i++){
		std::cout<<v[i]<<" ";
	}
	std::cout<<"\n\n";
}

void insertInArrayAfterPosition(std::vector<std::string> &v, std::string s, int pos){
	v.push_back("");
	for(int insertIndex = v.size() - 1; insertIndex >= pos + 1; insertIndex--){
		v[insertIndex] = v[insertIndex - 1];}
	v[pos + 1] = s;}

void insertInArrayBeforePosition(std::vector<std::string> &v, std::string s, int pos){
	v.push_back("");
	for(int insertIndex = v.size() - 1; insertIndex >= pos + 1; insertIndex--){
		v[insertIndex] = v[insertIndex - 1];}
	v[pos] = s;}

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
#define previousWord getPreviousWord(i, j, in)

std::string getPreviousWordAndIndexes(int &currentRowIndex, int &currentColIndex, StringMatrix &words){
	currentColIndex = currentColIndex - 1;
	while(currentColIndex < 0){
		currentRowIndex--;
		if(currentColIndex < 0){
			return "NOPREVIOUSWORD";
		}
		currentColIndex = words[currentRowIndex].size() - 1;
	}
	return words[currentRowIndex][currentColIndex];}

std::string getNextWord(int currentRowIndex, int currentColIndex, StringMatrix &words){
	int previousRowIndex = currentRowIndex;
	int previousColIndex = currentColIndex + 1;
	while(previousColIndex >= words[previousRowIndex].size()){
		previousRowIndex++;
		if(previousRowIndex >= words.size()){
			return "NONEXTWORD";}
		previousColIndex = 0;}
	return words[previousRowIndex][previousColIndex];}
#define nextWord getNextWord(i, j, in)

#define FirstLetterOf(x) x[0]


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

        else if( isDoubleOperator(currentLetter) ){ //...+ or ...+=... or >= BUT NOT >>
            if( lastCharacterWasDoubleOperator ){
                currentWord += currentLetter;
				print "Found double operator. Pushing it: ";
				print currentWord;
				print "\n";
                v.push_back(currentWord);
                currentWord = "";
                lastCharacterWasDoubleOperator = false;}
            else{
                if(currentWord.length() > 0){
					print "Found a (possible double) operator. Pushing word behind: ";
					print currentWord;
					print "\n";
                    v.push_back(currentWord);}
				if(currentLetter == '>'){
					lastCharacterWasDoubleOperator = false;}
				else{
					lastCharacterWasDoubleOperator = true;}
                currentWord = "";
                currentWord += currentLetter;
				}}

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

// singleton. resets after every class
class StaticMembers{public:

	StringMatrix words;
	int currentMember = -1;

	StaticMembers(){}

	void clear(){
		words.clear();
		currentMember = -1;}

	void addNewMember(std::vector<std::string> parsedLine){
		words.push_back(parsedLine);
		currentMember++;}


	std::string processCurrentMember(std::string staticMemberParentClass){
		bool memberWasInitialized = false;
		int indexOfEqual = words[currentMember].size() - 1;
		int indexOfObject = indexOfEqual;
		for(int i = 0; i<words[currentMember].size(); i++){
			if(words[currentMember][i] == "="){
				memberWasInitialized = true;
				indexOfEqual = i;
				indexOfObject = i - 1;
				break;}}
		std::string returnedLine = "";
		for(int i = 0; i<indexOfEqual; i++){
			returnedLine += words[currentMember][i] + " ";}
		returnedLine += ";";
		std::string changeLine = ""; //changes the current line in this class. it will be appended after the class ends
		for(int i = 0; i<words[currentMember].size(); i++){
			if(i == indexOfObject){
				changeLine += staticMemberParentClass + "::" + words[currentMember][indexOfObject] + " ";}
			else{
				changeLine += words[currentMember][i] + " ";}}
		words[currentMember].clear();
		words[currentMember].push_back(changeLine);
		return returnedLine;}
};

std::string parseCode(std::string pathToFile, Map<int>& map){

    StringMatrix in(0);
    StringMatrix out(0);

    readFileIntoWords(pathToFile, in);

    std::cout<<"Transforming code into cpp\n";

	bool isWritingString = false;

	out.reserve(in.size());	//this doesn't do anything, it just reserves so it runs faster!

	//Control Variables:
	bool nextWordIsImportPath 	= false;
	bool addParanthesisAtTheEnd	= false;
	bool addBracketAtTheEnd		= false;
	std::string currentClass	= "NONE";
	bool isInTemplate			= false;
	bool addStarAfterThisWord	= false;
	int currentTemplateLevel	= 0;	//increases when finds <, decreases when finds >
	StaticMembers staticMembers	= StaticMembers();
	bool thisLineWasStatic		= false;
	bool thisLineWasEndOfClass	= false;

	int nLinesInText = in.size();
	for(int i = 0; i<nLinesInText; i++){
		out.push_back( newEmptyStringVector );
		int nWordsInLine = in[i].size();
		out[i].reserve( nWordsInLine ); //same here. if we remove the 2 lines, it works still
		for(int j = 0; j<in[i].size(); j++){
			std::string inputWord = in[i][j];
			std::string outputWord = "";
			//CODE FOR INTERPRETING WORDS IS HERE

			// "standard.corn"
			if(nextWordIsImportPath){
				nextWordIsImportPath = false;
				inputWord = inputWord.substr(1, inputWord.length() - 2);
				outputWord = parseCode(inputWord, map);}

			// an OPERATOR
			else if(isStringOperator(inputWord)){	// + - = \ ...
				if(inputWord == ""){}
				check(";"){
					outputWord = "@";}
				check("."){
					if(map.getData(previousWord) == CLASSNAME){
						outputWord = "::";}
					else{
						outputWord = "->";}}
				check("["){
					// MAY BE VERY BUGGED. CHECK LATER
					int kCurrent = j;
					j = -1;	//cuz it will do the j++ and restart for all the line
					outputWord = "";
					out[i].clear();
					std::vector<std::string> kLine = std::vector<std::string>(in[i].size());
					int indexOfBracket = 0;
					for(int kIndex = 0; kIndex < in[i].size(); kIndex++){
						kLine[kIndex] = in[i][kIndex];}
					bool lineContainsBracket = true;

					while(lineContainsBracket){
						lineContainsBracket = false;
						for(int kIndex = 0; kIndex < kLine.size(); kIndex++){
							if(kLine[kIndex] == "["){
								indexOfBracket = kIndex;
								lineContainsBracket = true;
								break;}}
						if(lineContainsBracket == false){
							break;}
						int kStack = 0;
						int startGetIndex = 0;
						for(int kIndex = indexOfBracket; kIndex >= 0; kIndex--){
							startGetIndex = kIndex;
							if(isStringOperator(kLine[kIndex])){
								if(kLine[kIndex] == ")"){
									kStack++;}
								else if(kLine[kIndex] == "("){
									kStack--;
									if(kStack < 0){
										break;}}
								else{
									if(kStack == 0 && kLine[kIndex] != "["){
										startGetIndex++;
										break;}
									else{
										/*doNothng*/}}}}
						std::cout << "startGetIndex : " << startGetIndex << "\n";
						kStack = 0;
						int endGetIndex = 0;
						for(int kIndex = indexOfBracket + 1; kIndex < kLine.size(); kIndex++){
							endGetIndex = kIndex;
							if(kLine[kIndex] == "["){
								kStack++;}
							else if(kLine[kIndex] == "]"){
								kStack--;
								if(kStack < 0){
									break;}}}
						printArray(kLine);
						kLine[indexOfBracket] = ",";
						printArray(kLine);
						kLine[endGetIndex] = ")";
						printArray(kLine);
						insertInArrayBeforePosition(kLine, "(", startGetIndex);
						printArray(kLine);
						insertInArrayBeforePosition(kLine, "elem", startGetIndex);
						printArray(kLine);
						}	
					in[i] = kLine;
					printArray(in[i]);
					}
				check("]"){
					outputWord = ")";}
				check("<"){
					outputWord = "<";
					if(isInTemplate){
						currentTemplateLevel++;}
					}
				check(">"){
					outputWord = ">";
					if(isInTemplate){
						currentTemplateLevel--;
						if(currentTemplateLevel == 0){
							isInTemplate = false;}
						if(nextWord != "(" && code(nextWord) != CLASS){
							outputWord += "*";}


						// Object <...   >*    ob
							}
					}
				else{
					outputWord = inputWord;}
			}
			// a WORD...
			else{
				int currentWordAsInt = map.getData(inputWord);
				switch(currentWordAsInt){
					case NOT_FOUND:
						outputWord = inputWord;
						break;
					case IMPORT:
						outputWord = "\n";
						nextWordIsImportPath = true;
						break;
					case CLASS:
						outputWord = inputWord;
						addBracketAtTheEnd = true;
						map.push(LastWordOfInputLine, CLASSNAME);
						currentClass = LastWordOfInputLine;
						break;
					case CLASSNAME:
						outputWord = inputWord;
						/* adding pointers */
						if( isStringOperator(nextWord) ){	//probably Object < | Object > | Object , | new Object()
							if(nextWord == "<"){//the * is put above, at '//an OPERATOR' at '>'
								isInTemplate = true;}
							if(nextWord == ">" || nextWord == ","){
								addStarAfterThisWord = true;}
						}
						else if( code(nextWord) == NOT_FOUND ){ //probably Object ob
							addStarAfterThisWord = true;
						}
						//Object<Object> o = new Object<Object>()			Object<Object*>* o = new Object<Object>();
						//Object<Object, int, Object<Object>, bool> o = new ...
						//		v
						//Object<Object*, int, Object<Object*>*, bool>* ob = new Object....
						//Object<Object*>* ob
						//		v
						//Object<Object*>* ob
						//
						//template<class T,
						break;
					case BRACKET:
						outputWord = "}";
						thisLineWasEndOfClass = true;
						break;
					case PRIMITIVE:
						outputWord = inputWord;
						break;
					case IF:
						outputWord = "if(";
						addBracketAtTheEnd = true;
						break;
					case PUBLIC:
						outputWord = "public:";
						break;
					case PRIVATE:
						outputWord = "private:";
						break;
					case STATIC:
						thisLineWasStatic = true;
						outputWord = "static";
						break;



				}
			}
			if(addStarAfterThisWord){
				addStarAfterThisWord = false;
				outputWord += "*";
			}
			/*if(addStarBeforeThisWord){
				addStarBeforeThisWord = false;
				outputWord = "*" + outputWord;}
			if(addStarBeforeNextWord){
				addStarBeforeNextWord = false;
				addStarBeforeThisWord = true;}
			*/
			out[i].push_back(outputWord);
		}//END OF THE LINE TO PARSE


		// adding Brackets, Colons, etc
		if(thisLineWasEndOfClass){
			thisLineWasEndOfClass = false;
			for(int staticIter = 0; staticIter <= staticMembers.currentMember; staticIter++){
				LastWordOfOutputLine += "\n" + staticMembers.words[staticIter][0];}
			currentClass = "~~~";
			staticMembers.clear();
		}
		if(thisLineWasStatic){
			thisLineWasStatic = false;
			staticMembers.addNewMember(out[i]);
			out[i].clear();
			out[i].push_back(staticMembers.processCurrentMember(currentClass));}
		if(addParanthesisAtTheEnd){
			addParanthesisAtTheEnd = false;
			LastWordOfOutputLine += ")";}
		if(addBracketAtTheEnd){
			addBracketAtTheEnd = false;
			LastWordOfOutputLine += "{";}

	}//END OF THE WHOLE TEXT TO PARSE


	//formatting returned string (only for aesthetics, doesn't change anything)
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
