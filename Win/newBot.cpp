#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
	
	string newFileName;
	if(argc > 1) newFileName = argv[1];
	else newFileName = "newPlayer";
	
	string newHeader = "src/" + newFileName + ".h";
	string newCPP = "src/" + newFileName + ".cpp";
	
	string toSearch = "TemplateBot";
	string toReplace = newFileName;
	
	ifstream inFile;
	ofstream outFile;
	
	inFile.open("src/TemplateBot.h");
	outFile.open(newHeader.c_str());
	
	char line[200];
	while(inFile.getline(line, 200)) {
		string tempLine = line;
		int location;
		while(true) {
			location = (int)tempLine.find(toSearch);
			if(location != -1){
					tempLine.replace(location, toSearch.length(), toReplace);	
			}
			else break;
		}
		outFile << tempLine << endl;
	}
	inFile.close();
	outFile.close();
	
	inFile.open("src/TemplateBot.cpp");
	outFile.open(newCPP.c_str());
	
	while(inFile.getline(line, 200)) {
		string tempLine = line;
		int location;
		while(true) {
			location = (int)tempLine.find(toSearch);
			if(location != -1){
					tempLine.replace(location, toSearch.length(), toReplace);	
			}
			else break;
		}
		outFile << tempLine << endl;
	}
	inFile.close();
	outFile.close();
	
	return 0;
}