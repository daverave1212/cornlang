#ifndef OBJECT_FINDER_H_INCLUDED
#define OBJECT_FINDER_H_INCLUDED

#define pointer *
#define print ;std::cout<<
#define println ;std::cout<<"\n"<<


int charToLetterMapCode(const char &c)
{
    if( c > 47 && c < 58 )      // 1 2 3 ...
    {
        return c - 48;
    }
    if( c > 96 && c < 123 )     // a b c ...
    {
        return c - 87;
    }
    if( c > 64 && c < 91)       // A B C ...
    {
        return c - 29;
    }
    if( c == '_')
    {
        return 62;
    }
}
// 0 1 2 ... 9      =   0 1 2 ... 9
// a b c ...  Z     =   10 11 12 ... 35
// A B C ...  Z     =   36 37 38 ... 61
// 62               =   62
class Letter
{
public:

    Letter* nextLetter[63];
    std::string data = "nuthn m8";

    Letter()
    {
        resetLetter();
    }


    void resetLetter()
    {
        for(int i = 0; i < 63; i++)
        {
            nextLetter[i] = NULL;
        }
    }


};

class LetterMap
{
public:

    Letter* defaultLetter;

    void create()
    {
        defaultLetter = new Letter();
        defaultLetter -> resetLetter();
    }

    LetterMap()
    {
        defaultLetter = new Letter();
        defaultLetter->resetLetter();
    }

    void addWord(std::string word)
    {
        int wordLength = word.length();
        if(wordLength == 0)
            return;

        int currentLetterIndex = 0;
        Letter* parentLetterIterator = NULL;
        Letter* letterIterator = defaultLetter;

        while(currentLetterIndex < wordLength && letterIterator != NULL)
        {
            char wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            parentLetterIterator = letterIterator;
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++;
        }
        if(currentLetterIndex == wordLength)
        {
            return;
        }
        currentLetterIndex--;                   //Make 1 step back, because now it's 1 ahead
        letterIterator = parentLetterIterator;  //Make 1 step back, because now it's NULL or 1 ahead
        for(int i = currentLetterIndex; i < wordLength; i++)
        {
            int wordCurrentLetterCode = charToLetterMapCode(word[i]);
            letterIterator->nextLetter[wordCurrentLetterCode] = new Letter();
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
        }
        letterIterator -> data = "CEVA";

    }

    bool hasWord(std::string word)
    {
        int wordLength = word.length();
        if(wordLength == 0)
            return false;
        int currentLetterIndex = 0;
        Letter* letterIterator = defaultLetter;
        while(currentLetterIndex < wordLength && letterIterator != NULL)
        {
            int wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++;
        }
        if(currentLetterIndex == wordLength)
        {
            return true;
        }
        return false;
    }

    std::string getData(std::string word)
    {
        int wordLength = word.length();
        if(wordLength == 0)
            return false;
        int currentLetterIndex = 0;
        Letter* letterIterator = defaultLetter;
        while(currentLetterIndex < wordLength && letterIterator != NULL)
        {
            int wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++;
        }
        if(currentLetterIndex == wordLength)
        {
            return letterIterator -> data;
        }
        return "NULL";
    }


};


//-------------------------------- Template Map Below (copy paste from above) ------------------------------------

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

template <class T> class Map
{
public:

    MapLetter<T>* defaultLetter;
    int nElements = 0;
    T nullElement;

    void create(){
        defaultLetter = new MapLetter<T>('*');
        defaultLetter -> resetLetter();
    }

    Map(){
        defaultLetter = new MapLetter<T>('*');
        defaultLetter->resetLetter();
    }

    void push(std::string word, T Object){
        int wordLength = word.length();
        if(wordLength == 0)
            return;

        int currentLetterIndex = 0;
        MapLetter<T>* parentLetterIterator = defaultLetter;
        MapLetter<T>* letterIterator = defaultLetter->getNextLetter(word[0]);

        print "\n\tPushing word " print word print "\n";

        int i = 0;
        while(i < wordLength){
            char currentLetter = word[i];
            print "At parent letter "  print parentLetterIterator->getSelfLetter() print "\n";
            if(letterIterator == NULL){
                print "\tLetter pointer does not exist. Adding.\n";
                MapLetter<T>* auxiliaryLetter = new MapLetter<T>(currentLetter);
                print "\tCreated letter " print auxiliaryLetter->getSelfLetter() print "\n";
                letterIterator = auxiliaryLetter;
                print "letterIterator is " print letterIterator->getSelfLetter() print "\n";}
            else print "\nAt current letter " print letterIterator->getSelfLetter() print "\n";
            parentLetterIterator->setNextLetter(currentLetter, letterIterator);
            print "\tSet parentLetterIterator to " print parentLetterIterator->getSelfLetter() print "\n";
            parentLetterIterator = letterIterator;
            print "\tparentLetterIterator now at " print parentLetterIterator->getSelfLetter() print "\n";
            //letterIterator->setNextLetter(currentLetter, )
            if(letterIterator == NULL){
                print "Letter insertion success\n";
            }
            i++;
        }


        letterIterator = parentLetterIterator;
        i--;
        if(letterIterator -> hasData)
        {
            print "Word " print word print " already exists.\n";
            return;
        }
        letterIterator->setData(Object);
        print "Word " print word print " successfully pushed.\n";
    }

    bool isOccupied(std::string word){
        int wordLength = word.length();
        if(wordLength == 0)
            return false;
        int currentLetterIndex = 0;
        MapLetter<T>* letterIterator = defaultLetter;
        while(currentLetterIndex < wordLength && letterIterator != NULL)
        {
            int wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++;
        }
        if(currentLetterIndex == wordLength)
        {
            return true;
        }
        return false;
    }

    T getData(std::string word)
    {
        int wordLength = word.length();
        if(wordLength == 0)
            return false;
        int currentLetterIndex = 0;
        MapLetter<T>* letterIterator = defaultLetter;
        while(currentLetterIndex < wordLength && letterIterator != NULL)
        {
            int wordCurrentLetterCode = charToLetterMapCode(word[currentLetterIndex]);
            letterIterator = letterIterator->nextLetter[wordCurrentLetterCode];
            currentLetterIndex++;
        }
        if(letterIterator == NULL)
        {
            print "Word " << word << " not found: case NULL. Returning null.\n";
            return nullElement;
        }
        else if(currentLetterIndex == wordLength)
        {
            print "Found word " print word print ". Returning it.\n";
            return letterIterator -> data;
        }
        else
        {
            print "Word " << word << " not found: case LENGTH. Returning null.\n";
            return nullElement;
        }
    }


};


#endif // OBJECT_FINDER_H_INCLUDED
