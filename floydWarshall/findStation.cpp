#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <map>
using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	map<string, bool> vi;
	string filePath = "allPath.txt";
	ifstream readFile(filePath.data());
	string writeFilePath = "stations.txt";
	ofstream writeFile(writeFilePath.data());
	if(readFile.is_open()) {
		string line;
		while(getline(readFile, line)) {
			if(vi.count(line) || !writeFile.is_open()) continue;
			writeFile << line << "\n";
			vi[line] = true;
		}
	}
	writeFile.close();
	readFile.close();

}
