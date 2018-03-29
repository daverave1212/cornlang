#ifndef OBJECT_FINDER_H_INCLUDED
#define OBJECT_FINDER_H_INCLUDED

#define pointer *
#define print ;std::cout<<
#define println ;std::cout<<"\n"<<

int charToLetterMapCode(const char &c){
    if( c > 47 && c < 58 )   // 1 2 3 ...
        return c - 48;
    if( c > 96 && c < 123 )  // a b c ...
        return c - 87;
    if( c > 64 && c < 91)    // A B C ...
        return c - 29;
    if( c == '_')
        return 62;
}
// 0 1 2 ... 9      =   0 1 2 ... 9
// a b c ...  Z     =   10 11 12 ... 35
// A B C ...  Z     =   36 37 38 ... 61
// _                =   62

template <class T> class MapLetter {public:

    MapLetter<T>* nextLetter[63];
    char selfLetter;
    T data;
    bool hasData = false;

    MapLetter(char whatLetter) {
        selfLetter = whatLetter;
        resetLetter(); }

    MapLetter<T>* getNextLetter(char c) {
        char letterIndex = charToLetterMapCode(c);
        return nextLetter[letterIndex]; }

    void setNextLetter(char c, MapLetter<T>* n) {
        char letterIndex = charToLetterMapCode(c);
        nextLetter[letterIndex] = n; }

    void setData(T t) {
        data = t;
        hasData = true; }

    T getData(){
        return data;}

    void resetLetter() {
        for(int i = 0; i < 63; i++) {
            nextLetter[i] = NULL; } }

    char getSelfLetter(){
        return selfLetter;}


};

template <class T> class Map{public:

    MapLetter<T>* defaultLetter;
    int nElements = 0;
    T nullElement;



    Map(){
        defaultLetter = new MapLetter<T>('*');
        defaultLetter->resetLetter();}

    void create(){
        defaultLetter = new MapLetter<T>('*');
        defaultLetter -> resetLetter();}

    void setNullElementTo(T t){
        nullElement = t;}

    void push(std::string word, T Object){
        int wordLength = word.length();
        if(wordLength == 0)
            return;

        int currentLetterIndex = 0;
        MapLetter<T>* parentLetterIterator = defaultLetter;
        MapLetter<T>* letterIterator = defaultLetter->getNextLetter(word[0]);

        int i = 0;
        while(i < wordLength){
            char currentLetter = word[i];
            if(letterIterator == NULL){
                MapLetter<T>* auxiliaryLetter = new MapLetter<T>(currentLetter);
                letterIterator = auxiliaryLetter;}
            parentLetterIterator->setNextLetter(currentLetter, letterIterator);
            parentLetterIterator = letterIterator;
            if(i < wordLength - 1){
                letterIterator = letterIterator->getNextLetter(word[i+1]);}
            i++;}

        letterIterator = parentLetterIterator;
        if(letterIterator -> hasData) {
            print "Word " print word print " already exists.\n";
            return; }
        letterIterator->setData(Object);
        print "Word " print word print " successfully pushed.\n";
        return;}

    bool isOccupied(std::string word) {
        int wordLength = word.length();
        if(wordLength == 0)
            return false;
        int currentLetterIndex = 0;
        MapLetter<T>* letterIterator = defaultLetter;
        while(currentLetterIndex < wordLength && letterIterator != NULL) {
            int wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++; }
        if(currentLetterIndex == wordLength) {
            return true; }
        return false; }


    T getData(std::string word) {
        if(word.length() == 0)
            return false;
        int wordLength = word.length();


        int currentLetterIndex = 0;
        MapLetter<T>* letterIterator = defaultLetter;

        while(currentLetterIndex < wordLength && letterIterator != NULL) {
            int wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++; }
        if(letterIterator == NULL) {
            print "Word " << word << " not found: case NULL. Returning null.\n";
            return nullElement; }
        else if(currentLetterIndex == wordLength) {
            if(letterIterator->hasData){
                print "Found word " print word print ". Returning it.\n";
                return letterIterator -> data;
            }
            }
    }


};


#endif // OBJECT_FINDER_H_INCLUDED
