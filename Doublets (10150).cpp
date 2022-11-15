#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
// #include <bits/stdc++.h> /* This file is not available on local machine, but it is needed to run on online judge */
using namespace std;

vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

/* Build adjacent list for each word in dictionary */
unordered_map<string, vector<string>> buildGraph(unordered_set<string>& dictionary) {
	unordered_map<string, vector<string>> graph;
	for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
		string curr = *it;
		int len = curr.length();
		for (int i = 0; i < len; ++i) {
			char ch = curr[i];
			for (int j = 0; j < 26; ++j) {
				string temp = curr;
				if (letters[j] != ch) {
					temp[i] = letters[j];
					if (dictionary.find(temp) != dictionary.end())
						graph[curr].push_back(temp);
				}
			}
		}
	}
	return graph;
}

/* Parse each testcase */
pair<string, string> parse_line(string& str) {
	string start = "", end = "";
	int breakPoint = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] != ' ')
			start += str[i];
		else {
			breakPoint = i + 1;
			break;
		}
	}
	for (int i = breakPoint; i < str.length(); ++i)
		end += str[i];
	return { start, end };
}

/* Use Dijkstras' algorithm to find the shortest path */
vector<string> shortestPath(unordered_map<string, vector<string>>& graph, string& start, string& end) {
	if (graph.find(start) == graph.end() || graph.find(end) == graph.end())
		return { "No solution." };
	unordered_map<string, int> distances;
	for (auto it = graph.begin(); it != graph.end(); ++it)
		distances[it->first] = INT_MAX;
	distances[start] = 0;
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
	pq.push({ distances[start], start });
	while (!pq.empty()) {
		auto curr = pq.top();
		pq.pop();
		int currWeight = curr.first;
		string currWord = curr.second;
		for (int i = 0; i < graph[currWord].size(); ++i) {
			string nextWord = graph[currWord][i];
			int nextWeight = currWeight + 1;
			if (distances[nextWord] > nextWeight) {
				distances[nextWord] = nextWeight;
				pq.push({ distances[nextWord], nextWord });
			}
		}
	}
	if (distances[end] == INT_MAX)
		return { "No solution." };
	vector<string> res;
	int dist = distances[end];
	string curr = end;
	while (dist >= 0) {
		res.push_back(curr);
		if (curr == start)
			break;
		bool flag = false;
		for (int i = 0; i < graph[curr].size(); ++i) {
			if (distances[graph[curr][i]] == distances[curr] - 1) {
				curr = graph[curr][i];
				dist -= 1;
				flag = true;
			}
			if (flag == true)
				break;
		}
	}
	reverse(res.begin(), res.end());
	return res;
}

int main() {

	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}

	/*
	// For online test
	vector<string> text;
	string line;
	while (getline(cin, line))
		text.push_back(line);
	*/

	unordered_set<string> dictionary;
	int breakPoint = 0;
	for (int i = 0; i < text.size(); ++i) {
		if (text[i] != "")
			dictionary.insert(text[i]);
		else {
			breakPoint = i + 1;
			break;
		}
	}
	unordered_map<string, vector<string>> graph = buildGraph(dictionary);
	for (int i = breakPoint; i < text.size(); ++i) {
		pair<string, string> curr = parse_line(text[i]);
		string start = curr.first, end = curr.second;
		vector<string> res = shortestPath(graph, start, end);
		for (int j = 0; j < res.size(); ++j)
			cout << res[j] << endl;
		cout << endl;
	}
	return 0;
}