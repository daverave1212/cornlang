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

int main(int argc, char* argv[])
{
	Map<int> myMap;
	initMap(myMap);
	int x;

	if(argc < 3){
		goto INTHISFOLDER;}
	else{
		ofstream outFullPath(argv[2]);
		outFullPath << "#include <iostream>\n";
		outFullPath << "#include <vector>\n";
		outFullPath << "#include <windows.h>\n";
		outFullPath << "#include <time.h>\n";
		outFullPath << "#include \"standard_corn.h\"\n";
		outFullPath << "CornStream cornStream;\n";
		outFullPath << "\n";
		outFullPath << parseCode(argv[1], myMap);
		//cin>>x;
		return 0;
	}


	INTHISFOLDER:
		ofstream out("testcorn.txt");
		out << "#include <iostream>\n";
		out << "#include <vector>\n";
		out << "#include <windows.h>\n";
		out << "#include \"standard_corn.h\"\n";
		out << "CornStream cornStream;\n\n";
		out << parseCode("TestCorn.corn", myMap);
		return 0;

}
