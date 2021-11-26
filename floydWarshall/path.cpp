#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

vector<int> stations;
vector<int> ans;
vector<vector<int> > allPath;
bool vi[140];

void f (int cnt) {
	if(cnt == 2) {
		allPath.push_back(ans);
		return;
	}
	for(int i = 0; i < stations.size(); i++) {
		if(vi[i]) continue;
		vi[i] = true;
		ans.push_back(stations[i]);
		f(cnt + 1);
		vi[i] = false;
		ans.pop_back();
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int s;
	for(int i = 0 ; i < 111; i++) {
		cin >> s;
		stations.push_back(s);
	}
	f(0);
	string filePath = "permutation.txt";
	ofstream writeFile(filePath.data());
	if(writeFile.is_open()) {
		for(auto p : allPath) {
			string insert = "INSERT INTO station_from_to(`from`, `to`) VALUES(";
			for(auto i : p) {
				insert += "\'";
				insert += to_string(i);
				insert += "\'";
				insert += ", ";
//				writeFile << i << " ";
			}
//			writeFile << "\n";
			insert.pop_back();
			insert.pop_back();
			insert += ");";
			writeFile << insert << "\n";
		}
		writeFile.close();
	}
}
