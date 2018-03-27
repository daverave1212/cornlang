//AODASNDSNODNAIODNOSAI


#include <iostream>
#include <vector>
#include "parser.h"
#include "object_finder.h"

using namespace std;

ofstream out("testcorn.txt");

int main()
{
    parseCode("TestCorn.corn");
    //out << parseCode("TestCorn.corn");
    return 0;

    //vector<string> v;
    //string input = "for(int i=0; i<340; i++){";

    //splitStringIntoWords(input, v);
    //printArray(v);

    //parseCode("TestCorn.corn");
    Map<int> m;
    m.create();
    m.setNullElementTo(-1337);

    m.push("doggo", 10);
    m.push("d", 20);
    m.push("dog", 30);
    m.push("do", 40);
    m.push("dog", 50);
    m.push("d", 60);
    cout<<"\n\n\n";
    cout<<m.getData("doggo")<<" - doggo \n";
    cout<<m.getData("d")<<" - d \n";
    cout<<m.getData("dog")<<" - dog \n";
    cout<<m.getData("dag")<<" - dag \n";
    cout<<m.getData("do")<<" - do \n";
    cout<<m.getData("dog")<<" - dog \n";
    cout<<m.getData("degge")<<" - degge \n";
    cout<<m.getData("d")<<" - d \n";
    cout<<m.getData("dogge")<<" - dogge \n";
    cout<<m.getData("doggox")<<" - doggox \n";
    return 0;

    m.push("doggo", 1337);
    m.push("doggo", 420);
    cout<<m.getData("dog")<<endl;
    cout<<m.getData("doggo")<<endl;
    return 0;

}
