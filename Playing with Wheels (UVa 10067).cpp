// Playing with Wheels (UVa 10067).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
//#include <bits/stdc++.h> // Uncomment this line when run the program on OJ
using namespace std;

string parse_line(string& str) {
	string res = "";
	int len = str.length();
	for (int i = 0; i < len; ++i)
		if (str[i] != ' ')
			res += str[i];
	return res;
}

int shortestPath(string& startCom, string& endCom, unordered_set<string>& blocks) {
	unordered_set<string> visited;
	queue<string> q;
	int step = 0;
	if (startCom == endCom)
		return 0;
	if (blocks.find(endCom) != blocks.end())
		return -1;
	q.push(startCom);
	while (!q.empty()){
		int size = q.size();
		for (int k = 0; k < size; k++){
			string curr = q.front();
			q.pop();
			if (curr == endCom)
				return step;
			for (int i = 0; i < 4; i++){
				char temp = curr[i];
				if (temp == '9') curr[i] = '0';
				else curr[i] = temp + 1;
				if (blocks.find(curr) == blocks.end() && visited.find(curr) == visited.end()){
					q.push(curr);
					visited.insert(curr);
				}
				if (temp == '0') curr[i] = '9';
				else curr[i] = temp - 1;
				if (blocks.find(curr) == blocks.end() && visited.find(curr) == visited.end()){
					q.push(curr);
					visited.insert(curr);
				}
				curr[i] = temp;
			}
		}
		step++;
	}
	return -1;
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
	// For test on OJ
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);
	*/

	int currLine = 0;
	int num_Cases = stoi(text[currLine++]);
	for (int i = 0; i < num_Cases; ++i) {
		string startCom = parse_line(text[currLine++]);
		string endCom = parse_line(text[currLine++]);
		int num_blocks = stoi(text[currLine++]);
		unordered_set<string> blocks;
		for (int j = 0; j < num_blocks; ++j) {
			string block = parse_line(text[currLine++]);
			blocks.insert(block);
		}
		currLine++;
		cout << shortestPath(startCom, endCom, blocks) << endl;
	}
	return 0;
}