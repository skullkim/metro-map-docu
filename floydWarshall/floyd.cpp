#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const int MAX = 1000;
const int INF = 987654321;
int path[MAX][MAX];
int graph[MAX][MAX];
int otherVal[MAX][MAX];
int otherVal2[MAX][MAX];
vector<int> tmp;
vector<int> stations;

void findPath(int from, int to) {
	int prev = path[from][to];
	if(from == prev) {
		tmp.push_back(from);
		return;
	}
	findPath(from, prev);
	findPath(prev, to);
}

void floyd(int s_len) {
	for(int mid = 0; mid < s_len; mid++) {
		for(int st = 0; st < s_len; st++) {
			for(int e = 0; e < s_len; e++) {
				int st_s = stations[st];
				int mid_s = stations[mid];
				int e_s = stations[e];
				if(graph[st_s][e_s] > graph[st_s][mid_s] + graph[mid_s][e_s]) {
					graph[st_s][e_s] = graph[st_s][mid_s] + graph[mid_s][e_s];
					otherVal[st_s][e_s] = otherVal[st_s][mid_s] + otherVal[mid_s][e_s];
					otherVal2[st_s][e_s] = otherVal2[st_s][mid_s] + otherVal2[mid_s][e_s];
					path[st_s][e_s] = mid_s;
				}
			}
		}
	}
	return;
}

void parseStrToInt(int& start, int& end, string path) {
	string s = "";
	string e = "";
	for(int i = 0; i < 3; i++) s += path[i];
	for(int i = 4; i < 7; i++) e += path[i];
	start = stoi(s);
	end = stoi(e);
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for(int i = 0, s; i < 110; i++) {
		cin >> s;
		stations.push_back(s);
	}
	int s_len = stations.size();
	for(int i = 0; i < s_len; i++) {
		for(int k = 0; k < s_len; k++) {
			int s1 = stations[i];
			int s2 = stations[k];
			graph[s1][s2] = INF;
			graph[s2][s1] = INF;
			otherVal[s1][s2] = INF;
			otherVal[s2][s1] = INF;
			otherVal2[s1][s2] = INF;
			otherVal2[s2][s1] = INF;
			path[s1][s2] = s1;
			path[s2][s1] = s2;
		}
	}
	int n1, n2, v, ov1, ov2;
	for(int i = 0; i < 139; i++) {
		cin >> n1 >> n2 >> v >> ov1 >> ov2;
		graph[n1][n2] = v;
		graph[n2][n1] = v;
		otherVal[n1][n2] = ov1;
		otherVal[n2][n1] = ov1;
		otherVal2[n1][n2] = ov2;
		otherVal2[n2][n1] = ov2;
	}
	
	floyd(s_len);

	string filePath = "permutation.txt";
	ifstream readFile(filePath.data());
	string writeFilePath = "minTimeAns.txt";
	ofstream writeFile(writeFilePath.data());
	if(readFile.is_open()) {
		string line;
		while(getline(readFile, line)) {
			int start, end;
            tmp.clear();
			parseStrToInt(start, end, line);
			findPath(start, end);
			if(writeFile.is_open()) {
				writeFile << start << " " << end << " " << graph[start][end] << " " << otherVal[start][end] << " " << otherVal2[start][end] << " ";
				for(auto p : tmp) {
					writeFile << p << " ";
				}
				writeFile << "\n";
			}
//			cout << graph[start][end];
//			for(auto p : tmp) {
//				cout << p << " ";
//			}
//			cout << endl;
		}
		writeFile.close();
		readFile.close();
	}
}
