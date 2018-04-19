// Version:     0.08
//THIS IS IN GITHUB REPOSITORY
//THE PROJECT DOES NOTTTT COPY THEM INTO THE WORKING DIR
//IT WORKS DIRECTLY WITH THOSE
//WHICH IS AWESOME


#include <iostream>
#include <vector>
#include "parser.h"
#include "object_finder.h"
#include "map_init.h"

using namespace std;

ofstream out("testcorn.txt");



int main()
{
    START:

    Map<int> myMap;
    initMap(myMap);
    out << parseCode("TestCorn.corn", myMap);
    //out << "crocodil";
   // return 0;
    //return 0;
    int x;
    cin>>x;
   // goto START;

    Map<int> m;
    m.create();
    m.setNullElementTo(-1337);

    m.push("Gica", 10);

    cout<<"\n\n\n";
    cout<<m.getData("Gicalau")<<" - Gicalau \n";
    cout<<m.getData("Gic")<<" - Gic \n";
    cout<<m.getData("Gi")<<" - Gi \n";
    cout<<m.getData("G")<<" - G \n";

    return 0;

    m.push("doggo", 1337);
    m.push("doggo", 420);
    cout<<m.getData("dog")<<endl;
    cout<<m.getData("doggo")<<endl;



    return 0;

}
