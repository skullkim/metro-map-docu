#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const int MAX = 1000;
const int INF = 987654321;
int path[MAX][MAX];
vector<int> tmp;

void findPath(int from, int to) {
	int prev = path[from][to];
	if(from == prev) {
		tmp.push_back(from);
		return;
	}
	findPath(from, prev);
	findPath(prev, to);
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int graph[MAX][MAX];
	vector<int> stations;
	for(int i = 0, s; i < 139; i++) {
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
	int from, to;
	cin >> from >> to;
	cout << graph[from][to] << "\n";
	tmp.clear();
	findPath(from, to);
	tmp.push_back(to);
	for(auto p : tmp) {
		cout << p << " ";
	}
	cout << "\n";
}
