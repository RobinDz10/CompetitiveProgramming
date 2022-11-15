#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<string> parseLine(string& currLine) {
	vector<string> res;
	int comma_pointer = 0, pos = 0;
	string str = "";
	bool has_space = true;
	while (pos < currLine.length()) {
		if (currLine[pos] == ':') {
			res.push_back(str);
			break;
		}
		else {
			if (currLine[pos] == ',') {
				if (comma_pointer < 1) {
					str += currLine[pos];
					pos++;
					comma_pointer++;
				}
				else {
					comma_pointer = 0;
					res.push_back(str);
					str = "";
					pos += 2;
				}
			}
			else {
				str += currLine[pos];
				pos++;
			}
		}
	}
	return res;
}

void buildGraph(unordered_map<string, unordered_set<string>>& graph, unordered_set<string>& allNames, int start_line, int end_line, vector<string>& text) {
	for (int i = start_line; i <= end_line; ++i) {
		vector<string> names = parseLine(text[i]);
		for (int j = 0; j < names.size(); ++j) {
			string currName = names[j];
			allNames.insert(currName);
			if (graph.find(currName) == graph.end())
				graph[currName] = unordered_set<string>();
			for (int k = 0; k < names.size(); ++k) {
				if (k != j)
					graph[currName].insert(names[k]);
			}
		}
	}
	return;
}

/* Dijkstra's algorithm */
unordered_map<string, int> findDistance(unordered_map<string, unordered_set<string>>& graph, unordered_set<string>& allNames) {
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
	pq.push({ 0, "Erdos, P." });
	unordered_map<string, int> distances;
	for (auto it = allNames.begin(); it != allNames.end(); ++it)
		distances[*it] = INT_MAX;
	distances["Erdos, P."] = 0;
	while (!pq.empty()) {
		string currName = pq.top().second;
		int currDist = pq.top().first;
		pq.pop();
		for (auto it = graph[currName].begin(); it != graph[currName].end(); ++it) {
			string nextName = *it;
			if (distances[nextName] > currDist + 1) {
				distances[nextName] = currDist + 1;
				pq.push({ distances[nextName], nextName });
			}
		}
	}
	return distances;
}

int main() {
	// For local Test:
	// If need to run the program in local machine, use the code block from line 87 to line 95

	ifstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			text.push_back(line);
		}
		myFile.close();
	}

	/*
	// For online test:
	// If need to run the program online, use the code block from line 102 to line 106
	// If in onlinejudge.org, we need to add #include<bits/stdc++.h> at the beginning of this file, otherwise it will be compiler error (INT_MAX)

	string line;
	vector<string> text;
	while (getline(cin, line)) {
		text.push_back(line);
	}
	*/

	// Main Program
	int total_cases = stoi(text[0]), case_pointer = 1;
	int line_pointer = 1;
	while (line_pointer < text.size() && text[line_pointer] != "") {
		if (text[line_pointer][0] >= '0' && text[line_pointer][0] <= '9') {
			int num1 = 0, num2 = 0, tempPos = 0;
			for (; tempPos < text[line_pointer].size(); ++tempPos) {
				if (text[line_pointer][tempPos] == ' ') {
					tempPos++;
					break;
				}
				num1 = num1 * 10 + (text[line_pointer][tempPos] - '0');
			}
			for (; tempPos < text[line_pointer].size(); ++tempPos)
				num2 = num2 * 10 + (text[line_pointer][tempPos] - '0');
			int end1 = line_pointer + num1, end2 = end1 + num2;
			unordered_map<string, unordered_set<string>> graph;
			unordered_set<string> allNames;
			buildGraph(graph, allNames, line_pointer + 1, end1, text);
			
			unordered_map<string, int> case_Res = findDistance(graph, allNames);
			cout << "Scenario " << case_pointer << endl;
			for (int i = end1 + 1; i <= end2; ++i) {
				string test_name = text[i];
				if (case_Res.find(test_name) == case_Res.end())
					cout << test_name << " infinity" << endl;
				else if (case_Res[test_name] == INT_MAX)
					cout << test_name << " infinity" << endl;
				else
					cout << test_name << " " << case_Res[test_name] << endl;
			}
			line_pointer = end2 + 1;
			case_pointer++;
		}
	}
	return 0;
}