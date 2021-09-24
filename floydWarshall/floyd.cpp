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
	int n1, n2, v;
	for(int i = 0; i < s_len; i++) {
		for(int k = 0; k < s_len; k++) {
			int s1 = stations[i];
			int s2 = stations[k];
			graph[s1][s2] = INF;
			graph[s2][s1] = INF;
			path[s1][s2] = s1;
			path[s2][s1] = s2;
		}
	}
	for(int i = 0; i < 139; i++) {
		cin >> n1 >> n2 >> v;
		graph[n1][n2] = v;
		graph[n2][n1] = v;
	}
	
	floyd(s_len);

	string filePath = "permutation.txt";
	ifstream readFile(filePath.data());
	string writeFilePath = "minPathAns.txt";
	ofstream writeFile(writeFilePath.data());
	if(readFile.is_open()) {
		string line;
		while(getline(readFile, line)) {
			int start, end;
            tmp.clear();
			parseStrToInt(start, end, line);
			findPath(start, end);
//			string sql = "INSERT INTO min_cost_value(minValue, fromToId) VALUES(\'";
//			sql += to_string(graph[start][end]);
//			sql += "\', (SELECT id FROM station_from_to WHERE `from`=\'";
//			sql += to_string(start);
//			sql += "\' AND `to`=\'";
//			sql += to_string(end);
//			sql += "\'));";
			if(writeFile.is_open()) {
//				writeFile << sql << "\n";
				writeFile << start << " " << end << " " << graph[start][end] << " ";
				for(auto p : tmp) {
//					string sql2 = "INSERT INTO min_cost(station, minCostId) VALUES(\'";
//					sql2 += to_string(p);
//					sql2 += "\', (SELECT id FROM min_cost_value ORDER BY id DESC LIMIT 1));";
//					writeFile << sql2 << "\n";
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
