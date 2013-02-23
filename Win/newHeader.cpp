#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
	
	string fplr, splr;
	ofstream outFile;
	outFile.open("src/BotHeader.h");
	
	if(argc == 1) {
		fplr = "SampleBot";
		splr = "SampleMirror";
	}
	else if(argc == 2) {
		fplr = "SampleBot";
		splr = argv[1];
	}
	else {
		fplr = argv[1];
		splr = argv[2];
	}
	
	if(fplr == splr) {
		outFile << "#include \"" << fplr << ".h\"" << endl;
	}
	else {
		outFile << "#include \"" << fplr << ".h\"" << endl;
		outFile << "#include \"" << splr << ".h\"" << endl;
	}
	outFile << endl;
	outFile << "typedef " << fplr << " P1;" << endl;
	outFile << "typedef " << splr << " P2;" << endl;
	
	outFile.close();
	
	return 0;
}