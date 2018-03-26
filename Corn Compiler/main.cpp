//AODASNDSNODNAIODNOSAI


#include <iostream>
#include <vector>
#include "parser.h"
#include "object_finder.h"

using namespace std;



int main()
{

    //vector<string> v;
    //string input = "for(int i=0; i<340; i++){";

    //splitStringIntoWords(input, v);
    //printArray(v);

    //parseCode("TestCorn.corn");
    Map<int> m;
    m.create();
    m.push("d", 1337);
    m.push("d", 1337);
    return 0;

    m.push("doggo", 1337);
    m.push("doggo", 420);
    cout<<m.getData("dog")<<endl;
    cout<<m.getData("doggo")<<endl;
    return 0;

}
