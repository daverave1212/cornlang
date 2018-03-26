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
    m.push("doggo", 1337);
    m.push("d", 420);
    m.push("dog", 19990);
    m.push("do", 2345);
    m.push("dog", 19990);
    m.push("d", 19990);
    cout<<m.getData("doggo")<<" - doggo \n";
    cout<<m.getData("d")<<" - d \n";
    cout<<m.getData("dog")<<" - dog \n";
    cout<<m.getData("do")<<" - do \n";
    cout<<m.getData("dog")<<" - dog \n";
    cout<<m.getData("d")<<" - d \n";
    return 0;

    m.push("doggo", 1337);
    m.push("doggo", 420);
    cout<<m.getData("dog")<<endl;
    cout<<m.getData("doggo")<<endl;
    return 0;

}
