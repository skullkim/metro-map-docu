#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
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
	//if(s == "217" || e == "217") cout << s << endl;
	//cout << s << endl;
	start = stoi(s);
	end = stoi(e);
}

string insertMinValue(const string target, int start, int end) {
	string sql = "INSERT INTO min_";
	sql += target;
	sql += "_value(minValue, fromToId) VALUES(\'";
	sql += to_string(graph[start][end]);
	sql += "\', (SELECT id FROM station_from_to WHERE `from`=\'";
	sql += to_string(start);
	sql += "\' AND `to`=\'";
	sql += to_string(end);
	sql += "\'));";
	return sql;
}

string insertOtherValue(const string targetLower, const string targetUpper, int start, int end, string ov1, string ov2) {
	string sql3 = "INSERT INTO min_";
	sql3 += targetLower;
	sql3 += "_other_values(";
	sql3 += ov1;
	sql3 += ", ";
	sql3 += ov2;
	sql3 += ", min";
	sql3 += targetUpper;
	sql3 += "ValueId) VALUES(\'";
	sql3 += to_string(otherVal[start][end]);
	sql3 += "\', \'";
	sql3 += to_string(otherVal2[start][end]);
	sql3 += "\', @fromToId);";
	return sql3;
}

string insertSqlVal(const string target) {
	string sqlVal = "SET @fromToId=(SELECT id FROM min_";
	sqlVal += target;
	sqlVal += "_value ORDER BY id DESC LIMIT 1);";
	return sqlVal;
}

string insertPath(const string targetLower, const string targetUpper, auto val) {
	string sql2 = "INSERT INTO min_";
	sql2 += targetLower;
	sql2 += "(station, min";
	sql2 += targetUpper;
	sql2 += "Id) VALUES(\'";
	sql2 += to_string(val);
	sql2 += "\', @fromToId);";
	return sql2;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for(int i = 0, s; i < 111; i++) {
		cin >> s;
		if(s == 217) cout << s << endl;
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
			otherVal[s1][s2] = INF;
			otherVal[s2][s1] = INF;
			otherVal2[s1][s2] = INF;
			otherVal2[s2][s1] = INF;
			path[s1][s2] = s1;
			path[s2][s1] = s2;
		}
	}
	int ov1, ov2;
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
	const string targetLower = "distance";
	const string targetUpper = "Distance";
	const string otherV1 = "time";
	const string otherV2 = "cost";
	string writeFilePath = "minPathAns.sql";
	ofstream writeFile(writeFilePath.data());
	if(readFile.is_open()) {
		string line;
		while(getline(readFile, line)) {
			int start, end;
            tmp.clear();
			parseStrToInt(start, end, line);
			findPath(start, end);
			string sql = insertMinValue(targetLower, start, end);
			string sqlVal = insertSqlVal(targetLower);
			if(writeFile.is_open()) {
				writeFile << sql << "\n";
				writeFile << sqlVal << "\n";
				string sql3 = insertOtherValue(targetLower, targetUpper, start, end, otherV1, otherV2);
				if(start == 217) cout << "start" << endl;
				writeFile << sql3 << "\n";
				for(auto p : tmp) {
					string sql2 = insertPath(targetLower, targetUpper, p);
					writeFile << sql2 << "\n";

				}
				string sql2 = insertPath(targetLower, targetUpper, end);
				writeFile << sql2 << "\n";
				writeFile << "\n";
			}
		}
		writeFile.close();
		readFile.close();
	}
}
