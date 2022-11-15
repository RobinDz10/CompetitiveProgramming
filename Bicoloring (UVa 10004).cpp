// Bicoloring (UVa 10004).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
//#include <bits/stdc++.h> //Uncomment this line when run the code on OJ
using namespace std;

vector<int> parse_line(string& str) {
	vector<int> vec;
	int num1 = 0, num2 = 0, breakPoint = -1, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ') {
			num1 = num1 * 10 + (str[i] - '0');
			if (i == len - 1)
				break;
		}
		else {
			breakPoint = i;
			break;
		}
	}
	vec.push_back(num1);
	if (breakPoint == -1) return vec;
	for (int i = breakPoint + 1; i < len; ++i)
		num2 = num2 * 10 + (str[i] - '0');
	vec.push_back(num2);
	return vec;
}

bool canColor(vector<vector<int>>& graph) {
	int num_nodes = graph.size();
	vector<int> colors(num_nodes, -1);
	queue<int> q;
	q.push(0);
	int currColor = 1;
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; ++i) {
			int curr_node = q.front();
			colors[curr_node] = currColor;
			q.pop();
			for (int j = 0; j < graph[curr_node].size(); ++j) {
				int next_node = graph[curr_node][j];
				if (colors[next_node] == currColor)
					return false;
				if (colors[next_node] == -1)
					q.push(next_node);
			}
		}
		if (currColor == 1) currColor = 2;
		else currColor = 1;
	}
	return true;
}

int main() {
	/*
	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<vector<int>> text;
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			vector<int> tempLine = parse_line(line);
			text.push_back(tempLine);
		}
		myFile.close();
	}
	*/

	// For test on OJ
	string line;
	vector<vector<int>> text;
	while (getline(cin, line)) {
		vector<int> tempLine = parse_line(line);
		text.push_back(tempLine);
	}

	int currLine = 0;
	for (; currLine < text.size(); ) {
		if (text[currLine][0] == 0) break;
		int num_nodes = text[currLine++][0], num_edges = text[currLine++][0];
		vector<vector<int>> graph(num_nodes);
		for (int j = 0; j < num_edges; ++j) {
			int node1 = text[currLine + j][0], node2 = text[currLine + j][1];
			graph[node1].push_back(node2);
			graph[node2].push_back(node1);
		}
		currLine += num_edges;
		if (canColor(graph)) cout << "BICOLORABLE." << endl;
		else cout << "NOT BICOLORABLE." << endl;
	}
	return 0;
}
