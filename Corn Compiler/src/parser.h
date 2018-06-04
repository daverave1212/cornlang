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

#define StringVector std::vector<std::string>
#define newEmptyStringVector std::vector<std::string>(0)
#define StringMatrix std::vector<std::vector<std::string>>

#define ENDFOR }
#define FirstLetterIsOperator(x) ( x[0] >= 33 && x[0] <= 47 ) || ( x[0] >= 58 && x[0] <= 64 ) || ( x[0] >= 91 && x[0] <= 94 ) || ( x[0] == 96 ) || ( x[0] >= 193 && x[0] <= 196 )
#define FirstLetterIsNumber(x) ( x[0] >= 48 && x[0] <= 57 )
#define LastWordOfInputLine in[i][nWordsInLine - 1]
#define LastWordOfOutputLine out[i][out[i].size() - 1]
#define PreviousLastWordOfInputLine in[i][nWordsInLine - 2]
#define code(x) map.getData(x)
#define FirstLetterOf(x) x[0]
#define IsThisWordLastWordOfLine j == in[i].size() - 1

#define check(x) else if(inputWord == x)

void appendStringVector(StringVector &base, StringVector &appendix){
	for(int i = 0; i<appendix.size(); i++){
		base.push_back(appendix[i]);}}

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


inline bool isSpaceOrTab(char c){
    if(c == ' ' || c == '\t') return true;
    else return false;}

std::string singleOperatorCharacters = "()[]{};,.:";
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

std::string operatorCharacters = "()[]{};:,.!%&*|=-+<>";
inline bool isCharOperator(char c){
    if(operatorCharacters.find(c) != std::string::npos){
        return true;}
    else return false;}

std::string digitCharacters = "0123456789";
inline bool isStringNumber(std::string s){
	if(digitCharacters.find(s) != std::string::npos){
		return true;}
	else return false;}

inline bool isCharNumber(char c){
	if(digitCharacters.find(c) != std::string::npos){
		return true;}
	else return false;}

inline bool isStringOperator(std::string s){
	if(s.length() == 0 || s.length() > 2){
		return false;}
	if(isCharOperator(s[0])){
		return true;}
	else return false;}


inline bool isQuote(char c){
	if(c == QUOTECHARACTER){
		return true;}
	else return false;}

inline bool isStringEscaped(std::string s){
	if(s.length() < 2) return false;
	if(s[0] == '~' && s[1] == '~'){
		return true;}
	else return false;}


inline std::string parseEscapedString(std::string s){
	return s.substr(2, s.length() - 2);
}

void splitStringIntoWords(std::string &s, std::vector<std::string>& v){
	print "Splitting string into words...\n";

    std::string currentWord = "";
    bool lastCharacterWasDoubleOperator   = false;    // ONLY FOR DOUBLE OPERATORS
	bool isProcessingString = false;


    for(int i = 0; i<s.length(); i++){
        char currentLetter = s[i];

		if( isQuote(currentLetter) ){
			if( !isProcessingString ){
				if(currentWord.length() > 0){
					v.push_back(currentWord);
					currentWord = "";}
				currentWord = QUOTESTRING;
				isProcessingString = true;
				lastCharacterWasDoubleOperator = false;}
			else{
				currentWord += currentLetter;
				v.push_back(currentWord);
				currentWord = "";
				isProcessingString = false;}}

		else if(isProcessingString){
			currentWord += currentLetter;}

        else if( isSpaceOrTab(currentLetter) ){ //..."  "...
            if(currentWord.length() > 0){
                v.push_back(currentWord);
                currentWord = "";}
            lastCharacterWasDoubleOperator = false;}

        else if( isSingleOperator(currentLetter)){ //...(...
			std::cout<<"Found . and next letter is "<<s[i+1]<<std::endl;
			if(s[i+1] == 'l'){
				std::cout<<">>>>>>>>> HERE\n";
			}
			if(currentLetter == '.' && i < s.size() - 1){
				if(isCharNumber(s[i+1])){
					std::cout<<"Also here. It won't split\n";
					// don't split here...
					currentWord += currentLetter;}
				else{
					if(currentWord.length() > 0){
						v.push_back(currentWord);}
					currentWord = currentLetter;
					v.push_back(currentWord);
					currentWord = "";
					lastCharacterWasDoubleOperator = false;
				}
			}
			else{
				if(currentWord.length() > 0){
					v.push_back(currentWord);}
				currentWord = currentLetter;
				v.push_back(currentWord);
				currentWord = "";
				lastCharacterWasDoubleOperator = false;}
			}

        else if( isDoubleOperator(currentLetter) ){ //...+ or ...+=... or >= BUT NOT >>
            if( lastCharacterWasDoubleOperator ){
                currentWord += currentLetter;
                v.push_back(currentWord);
                currentWord = "";
                lastCharacterWasDoubleOperator = false;}
            else{
                if(currentWord.length() > 0){
                    v.push_back(currentWord);}
				if(currentLetter == '>'){
					lastCharacterWasDoubleOperator = false;}
				else{
					lastCharacterWasDoubleOperator = true;}
                currentWord = "";
                currentWord += currentLetter;
				}}

        else { //...aLetter... or 129287
            if(lastCharacterWasDoubleOperator){
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

	void addNewMember(std::vector<std::string> &parsedLine){
		words.push_back(parsedLine);
		currentMember++;}


	std::string processCurrentMember(std::string staticMemberParentClass, int startIndex){
		bool memberWasInitialized = false;
		int indexOfEqual = words[currentMember].size();
		int indexOfObject = indexOfEqual - 1;

		for(int i = 0; i<words[currentMember].size(); i++){	//
			if(words[currentMember][i] == "="){				//
				memberWasInitialized = true;				//
				indexOfEqual = i;							// find indexOfObject, indexOfEqual
				indexOfObject = i - 1;						//
				break;}}									//

		std::string returnedLine = "";
		for(int i = 0; i<indexOfEqual; i++){
			returnedLine += words[currentMember][i] + " ";}
		returnedLine += ";";

		std::string changeLine = ""; //changes the current line in this class. it will be appended after the class ends
		for(int i = startIndex; i<words[currentMember].size(); i++){
			if(i == indexOfObject){
				changeLine += staticMemberParentClass + "::" + words[currentMember][indexOfObject] + " ";}
			else{
				changeLine += words[currentMember][i] + " ";}}
		changeLine += ";";
		words[currentMember].clear();
		words[currentMember].push_back(changeLine);
		return returnedLine;}
};

void parseForLine(std::vector<std::string> &parsedLine){
	print "CALLING FOR";
	int colonIndex = -1;
	int equalIndex = 0;
	int startIndex = 1;		//pentru ca porneste de la urmatorul cuvant dupa 'for'
	int endIndex = parsedLine.size() -1;
	bool isLookingForEquals = true;	//only looks for the first equals
	bool userPutInt = false;
	for(int i = 0; i<parsedLine.size(); i++){
		if(parsedLine[i] == ":"){
			colonIndex = i;}
		else if(parsedLine[i] == "=" && isLookingForEquals){
			equalIndex = i;
			isLookingForEquals = false;}}
	if(colonIndex == -1) return;
	if(parsedLine[1] == "("){
		startIndex++;
		endIndex--;
		if(parsedLine[2] == "int"){
			startIndex++;
			userPutInt = true;}}
	else if (parsedLine[1] == "int"){
		startIndex++;
		userPutInt = true;}

	StringVector beforeEquals(0);
	StringVector afterEquals(0);
	StringVector afterColon(0);
	for(int i = startIndex; i<equalIndex; i++){
		beforeEquals.push_back(parsedLine[i]);}
	for(int i = equalIndex + 1; i<colonIndex; i++){
		afterEquals.push_back(parsedLine[i]);}
	for(int i = colonIndex + 1; i<=endIndex; i++){
		afterColon.push_back(parsedLine[i]);}
	StringVector finalLine(0);
	finalLine.push_back("for");
	finalLine.push_back("(");
	finalLine.push_back("int");
	appendStringVector(finalLine, beforeEquals);
	finalLine.push_back("=");
	appendStringVector(finalLine, afterEquals);
	finalLine.push_back("~~;");		//escapes the ; so it doesnt take it as 'end'
	appendStringVector(finalLine, beforeEquals);
	finalLine.push_back("<=");
	appendStringVector(finalLine, afterColon);
	finalLine.push_back("~~;");
	appendStringVector(finalLine, beforeEquals);
	finalLine.push_back("++");
	finalLine.push_back(")");
	parsedLine = finalLine;}

std::string parseCode(std::string pathToFile, Map<int>& map){

    StringMatrix in(0);
    StringMatrix out(0);

    readFileIntoWords(pathToFile, in);

    std::cout<<"Transforming code into cpp\n";

	bool isWritingString = false;

	out.reserve(in.size());	//this doesn't do anything, it just reserves so it runs faster!
	int nLinesInText = in.size();

	//Control Variables:
	bool nextWordIsImportPath 	= false;
	bool addParanthesisAtTheEnd	= false;
	bool addBracketAtTheEnd		= false;
	std::string currentClass	= "~~~";
	bool isInTemplate			= false;
	bool addStarAfterThisWord	= false;
	int currentTemplateLevel	= 0;	//increases when finds <, decreases when finds >
	int currentClassAndFunctionLevel = 0;
	StaticMembers staticMembers	= StaticMembers();
	int staticLineStartIndex 	= 0;
	bool thisLineWasStaticAttribute	= false;
	bool thisLineWasStaticMethod	= false;
	bool thisLineWasEndOfClass	= false;
	bool thisLineWasClassDefinition = false;
	bool isIgnoringEverything	= false;
	bool thisLineIsNextLineAfterClassDefinition = false;
	bool thisLineWasFunctionDefinition = false;
	bool isInTemplateDefinition = false;
	int indentationLevel		= 0;
	int extraIndentationLevel 	= 0;
	std::vector<int> indentations	= std::vector<int>(nLinesInText);


	for(int i = 0; i<nLinesInText; i++){
		out.push_back( newEmptyStringVector );
		int nWordsInLine = in[i].size();
		out[i].reserve( nWordsInLine ); //same here. if we remove the 2 lines, it works still

		bool addSemicolonAtTheEnd	= true;
		indentationLevel += extraIndentationLevel;
		extraIndentationLevel = 0;

		for(int j = 0; j<in[i].size(); j++){
			std::string inputWord = in[i][j];
			std::string outputWord = "";
			//CODE FOR INTERPRETING WORDS IS HERE

			if(inputWord[0] == "@"){
				if(inputWord[2] == "o"){
					isIgnoringEverything = false;
				}
			}

			else if(isIgnoringEverything){
				outputWord = inputWord;}

			// escaped word (~~)
			else if(isStringEscaped(inputWord)){
				outputWord = parseEscapedString(inputWord);}

			// "standard.corn"
			else if(nextWordIsImportPath){
				nextWordIsImportPath = false;
				inputWord = inputWord.substr(1, inputWord.length() - 2);
				outputWord = parseCode(inputWord, map);}

			// a NUMBER 123458
			else if(isStringNumber(inputWord)){
				outputWord = inputWord;}

			// an OPERATOR
			else if(isStringOperator(inputWord)){	// + - = \ ...

				if(inputWord == ""){}
				check(";"){
					extraIndentationLevel--;
					addSemicolonAtTheEnd = false;
					outputWord = ";}";}
				check("."){
					std::cout<< ">>>>>>>>>> HERE\n";
					if(map.getData(previousWord) == CLASSNAME){
						outputWord = "::";}
					else{
						outputWord = "->";}}
				check("["){
					print "setting j to -1";
					// MAY BE VERY BUGGED. CHECK LATER
					int kCurrent = j;
					j = -1;	//cuz it will do the j++ and restart for all the line
					outputWord = "";
					out[i].clear();
					std::vector<std::string> kLine = std::vector<std::string>(in[i].size());
					int indexOfBracket = 0;
					for(int kIndex = 0; kIndex < in[i].size(); kIndex++){			// copy every word from in to kLine
						kLine[kIndex] = in[i][kIndex];}
					bool lineContainsBracket = true;
					while(lineContainsBracket){
						lineContainsBracket = false;
						for(int kIndex = 0; kIndex < kLine.size(); kIndex++){		// find the position of the first [
							if(kLine[kIndex] == "["){
								indexOfBracket = kIndex;
								lineContainsBracket = true;
								break;}}
						if(lineContainsBracket == false){							// if no [ was found, end
							break;}
						int kStack = 0;
						int startGetIndex = 0;
						print "startGetIndex = " << startGetIndex << "\n";
						bool lastWordWasOperator = true;
						for(int kIndex = indexOfBracket; kIndex >= 0; kIndex--){	// from first [ to 0
							startGetIndex = kIndex;
							print "kIndex = " << kIndex <<", startGetIndex = " << startGetIndex << "\n";
							if(isStringOperator(kLine[kIndex])){				// if this word is an operator...
								lastWordWasOperator = true;
								if(kLine[kIndex] == ")"){					// if it's ( increase stack
									kStack++;}
								else if(kLine[kIndex] == "("){				// if it's ) decrease stack
									kStack--;
									if(kStack < 0){
										startGetIndex++;
										print "\t\tstartGetIndex = " << startGetIndex << "\n";
										break;}}
								else if(kStack == 0 && kLine[kIndex] != "["){
									startGetIndex++;
									print "\tstartGetIndex = " << startGetIndex << "\n";
									break;}}
							else if(!lastWordWasOperator){		//prevents return a[1]
								print "startGetIndex = " << startGetIndex << "\n";
								startGetIndex++;
								break;}
							else lastWordWasOperator = false;
						}
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
						kLine[indexOfBracket] = ",";
						kLine[endGetIndex] = ")";
						insertInArrayBeforePosition(kLine, "(", startGetIndex);
						printArray(kLine);
						insertInArrayBeforePosition(kLine, "elem", startGetIndex);
						printArray(kLine);}
					in[i] = kLine;
					printArray(in[i]);
					print "Done parsing for.\n";}
				check("]"){
					outputWord = ")";}
				check("<"){
					outputWord = "<";
					if(isInTemplate){
						currentTemplateLevel++;}
					if(isInTemplateDefinition){
						outputWord += "typename";
					}}
				check(">"){
					outputWord = ">";
					if(isInTemplate){
						currentTemplateLevel--;
						if(currentTemplateLevel == 0){
							isInTemplateDefinition = false;
							isInTemplate = false;}
						if(nextWord != "(" && code(nextWord) != CLASS){
							outputWord += "*";}}}
				check("@"){
					if(inputWord[2] == '+'){	//@C++
						isIgnoringEverything = true;
					}
				}
				check(":"){		//NEEDS TESTING
					std::cout<<": at i = " << i<< ", j = "<<j<<std::endl;
					if(IsThisWordLastWordOfLine){
						std::cout<<"End of line it was indeed"<<std::endl;
						extraIndentationLevel++;
						if(previousWord == "start"){
							outputWord = "";}
						else if(thisLineWasClassDefinition){
							std::cout<<"Class at i = " << i<< ", j = "<<j<<std::endl;
							if(in[i][j-2] == "extends"){
								outputWord = "{public:";}
							else{
								outputWord = ": public Object{public:";}}
						else if(addBracketAtTheEnd){
							print "\t > CACAC CAINE TAUR\n";
							outputWord = "";}
						else{									//void aFunction():
							std::cout<<"Function at i = " << i<< ", j = "<<j<<std::endl;
							thisLineWasFunctionDefinition = true;
							outputWord = "{";
							print "\t > CACAC CAINE TAUR ALRUN\n";
							currentClassAndFunctionLevel++;}}
					else {
						outputWord = inputWord;
						outputWord += "%%THERE IS AN ERROR HERE%%";
					}}
				else if(j != -1){
				    /*print "FOUND AN OPERATOR WE DEFINITELY DON'T KNOW. It's ";
                    print inputWord;
					print " at j = ";
					print j;
                    print "\n"; */
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
						currentClassAndFunctionLevel++;
						outputWord = inputWord;
						map.push(nextWord, CLASSNAME);
						currentClass = nextWord;
						thisLineWasClassDefinition = true;
						break;
					case TEMPLATE:
						isInTemplateDefinition = true;
						outputWord = "template";
						break;
					case CLASSNAME:
						outputWord = inputWord;
						/* adding pointers */
						/* VARIANT WITH 'of' keyword: allows both Array<x> a, and Array of <x> a */
						if( previousWord == "extends" ){			//class Something extends ~~Object~~ :
							//doNothing()
						}
						else if( previousWord == "class" ){
							//doNothing()
						}
						else {
							if( nextWord == "of"){
								isInTemplate = true;}
							else if( isStringOperator(nextWord) ){	//probably Object < | Object > | Object , | Object . | new Object() | (Object) o
								if(nextWord == "<"){				//the * is put above, at '//an OPERATOR' at '>'
									isInTemplate = true;}
								else if(nextWord == ">" || nextWord == "," || nextWord == ")"){
									addStarAfterThisWord = true;}}
							else{									//probably Object ob
								addStarAfterThisWord = true;}}
						break;
					case EXTENDS:
						outputWord = ": public";
						break;
					case BRACKET:
						extraIndentationLevel--;
						outputWord = "}";
						currentClassAndFunctionLevel--;
						if(currentClassAndFunctionLevel == 0){
							thisLineWasEndOfClass = true;}
						break;
					case PRIMITIVE:
						outputWord = inputWord;
						break;
					case DOES:
						outputWord = "{";
						currentClassAndFunctionLevel++;
						break;
					case IF:
						outputWord = "if(";
						addParanthesisAtTheEnd = true;
						addBracketAtTheEnd = true;
						break;
					case ELSE:
						outputWord = "else";
						addBracketAtTheEnd = true;
						break;
					case FOR:
						outputWord = "for";
						addBracketAtTheEnd = true;
						parseForLine(in[i]);
						break;
					case WHILE:
						outputWord = "while(";
						addParanthesisAtTheEnd = true;
						addBracketAtTheEnd = true;
						break;
					case PUBLIC:
						outputWord = "public:";
						break;
					case PRIVATE:
						outputWord = "private:";
						break;
					case STATIC:
						if(LastWordOfInputLine == "does" || LastWordOfInputLine == ":"){
							thisLineWasStaticMethod = true;}
						else{
							staticLineStartIndex = j + 1;
							thisLineWasStaticAttribute = true;}
						outputWord = "static";
						break;
					case OR:
						outputWord = "||";
						break;
					case AND:
						outputWord = "&&";
						break;
					case OF:
						outputWord = "";
						break;
					case START:
						addSemicolonAtTheEnd = false;
						outputWord = "int main(int argc, char* argv[]){";
						outputWord+= "srand(time(NULL));\n";
						outputWord+= "system(\"color f0\");\n";
						break;
					case FINISH:
						outputWord = "cout<<\"Program ended. Press enter.\";pause();return 0;}";
						break;
					case PRINT:
						outputWord = ";cornStream<<";
						break;
					case READ:
						outputWord = ";cin>>";
						break;

				}
			}
			if(addStarAfterThisWord){
				addStarAfterThisWord = false;
				outputWord += "*";}
			out[i].push_back(outputWord);
		}//END OF THE LINE TO PARSE, ADDING APPENDAGES AND POSTPROCESSING

		// adding Brackets, Colons, etc

		if(thisLineWasStaticMethod){
            thisLineWasStaticMethod = false;}
		if(thisLineWasStaticAttribute){
			thisLineWasStaticAttribute = false;
			staticMembers.addNewMember(out[i]);
			out[i].clear();
			out[i].push_back(staticMembers.processCurrentMember(currentClass, staticLineStartIndex));}
		if(addParanthesisAtTheEnd){
			addParanthesisAtTheEnd = false;
			LastWordOfOutputLine += " )";}
		if(addBracketAtTheEnd){
			addBracketAtTheEnd = false;
			addSemicolonAtTheEnd = false;
			LastWordOfOutputLine += "{";}
		if(addSemicolonAtTheEnd && out[i].size() > 0){
			LastWordOfOutputLine += ";";}
		if(thisLineIsNextLineAfterClassDefinition){
			thisLineIsNextLineAfterClassDefinition = false;
			if(out[i].size() > 0){
				out[i][0] = "string type = \"" + currentClass + "\" ;\t string getType(){ return type;}\n" + out[i][0];}
			else{
				out[i].push_back("string type = \"" + currentClass + "\";string getType(){ return type; }\n");}}
		if(thisLineWasEndOfClass){
			thisLineWasEndOfClass = false;
			for(int staticIter = 0; staticIter <= staticMembers.currentMember; staticIter++){
				LastWordOfOutputLine += "\n" + staticMembers.words[staticIter][0];}
			currentClass = "~~~";
			staticMembers.clear();}
		if(thisLineWasFunctionDefinition && currentClass != "~~~" && !thisLineWasClassDefinition){
			thisLineWasFunctionDefinition = false;
			print "Line " << i<<" is virtual now\n";
			if(out[i][0] == "static"){
				// dontMakeItStatic
			}
			else if(out[i][0] == "public" || out[i][0] == "private"){
				out[i][1] = "virtual " + out[i][1];
			}
			else out[i][0] = "virtual " + out[i][0];}
		if(thisLineWasFunctionDefinition){
			thisLineWasFunctionDefinition = false;}
		if(thisLineWasClassDefinition){
			thisLineWasClassDefinition = false;
			thisLineIsNextLineAfterClassDefinition = true;}
		indentations[i] = indentationLevel;

	}//END OF THE WHOLE TEXT TO PARSE


	// formatting returned string (only for aesthetics, doesn't change anything)
	// NO PARSING HERE, EVER
	std::string returnedString = "";
	for(int i = 0; i<out.size(); i++){
		if(out[i].size() > 0){
			std::string tabs = "";
			for(int tabIndex = 1; tabIndex<=indentations[i]; tabIndex++){
				tabs += "\t";}
			out[i][0] = tabs + out[i][0];}
		for(int j = 0; j<out[i].size(); j++){
			returnedString += out[i][j] + " ";}
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
