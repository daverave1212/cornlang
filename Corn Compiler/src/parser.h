#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

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

std::string singleOperatorCharacters = "()[]{};";
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

    std::string currentWord = "";
    bool lastCharacterWasDoubleOperator   = false;    // ONLY FOR DOUBLE OPERATORS
    bool lastCharacterWasSpace      = false;
    bool lastCharacterWasLetter     = false;

    for(int i = 0; i<s.length(); i++){
        char currentLetter = s[i];

        if( isSpaceOrTab(currentLetter) ){ //..."  "...
            if(currentWord.length() > 0){
                v.push_back(currentWord);
                currentWord = "";}
            lastCharacterWasDoubleOperator = false;
            lastCharacterWasSpace = true;}

        else if( isSingleOperator(currentLetter)){ //...(...
            if(currentWord.length() > 0){
                v.push_back(currentWord);}
            currentWord = currentLetter;
            v.push_back(currentWord);
            currentWord = "";
            lastCharacterWasSpace = false;
            lastCharacterWasDoubleOperator = false;}

        else if( isDoubleOperator(currentLetter) ){ //...+ or ...+=...
            lastCharacterWasSpace   = false;
            lastCharacterWasLetter  = false;
            if( lastCharacterWasDoubleOperator ){
                currentWord += currentLetter;
                v.push_back(currentWord);
                currentWord = "";
                lastCharacterWasDoubleOperator = false;}
            else if( lastCharacterWasDoubleOperator == false ){
                if(currentWord.length() > 0){
                    v.push_back(currentWord);}
                lastCharacterWasDoubleOperator = true;
                currentWord = "";
                currentWord += currentLetter;}}

        else { //...aLetter...
            lastCharacterWasLetter  = true;
            lastCharacterWasSpace   = false;
            if(lastCharacterWasDoubleOperator){
                v.push_back(currentWord);
                currentWord = "";
                lastCharacterWasDoubleOperator = false;}
            currentWord += currentLetter;}
    }
}

void readFileIntoWords(std::string &pathToFile, StringMatrix &inputWords){
    std::ifstream readFile(pathToFile);
    std::string currentLine = "";

    int currentLineIndex = 0;

    while(std::getline(readFile, currentLine)){
        print "pushing line n " << currentLineIndex << "...\n";
        //inputWords.push_back(newEmptyStringVector);
        print "pushed. splitting\n";
        splitStringIntoWords(currentLine, inputWords[currentLineIndex]);
        print "split\n";
        currentLineIndex++;}
}

void cornToCPP(StringMatrix &in, StringMatrix &out){

}

std::string parseCode(std::string pathToFile){

    StringMatrix inputWords(0);
    StringMatrix outputWords(0);

    readFileIntoWords(pathToFile, inputWords);

    cornToCPP(inputWords, outputWords);







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
