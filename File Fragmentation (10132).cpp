#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<unordered_map<int, vector<string>>> get_all_cases(vector<string>& text) {
	vector<unordered_map<int, vector<string>>> graph;
	int line = 1;
	while (line < text.size()) {
		unordered_map<int, vector<string>> single_case;
		int case_line = line;
		line = case_line;
		graph.push_back(single_case);
	}
	return graph;
}

/* Should use DP here, but I have no idea to solve it properly */
string getAnswer(unordered_map<int, vector<string>>& level) {
	return "";
}

int main() {
	/*
	// For online test
	string line;
	vector<string> text;
	while (getline(cin, line)) {
		text.push_back(line);
	}
	*/

	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			text.push_back(line);
		}
		myFile.close();
	}
	int num_cases = stoi(text[0]);
	vector<unordered_map<int, vector<string>>> vec = get_all_cases(text);
	vector<string> res;
	for (int i = 0; i < vec.size(); ++i)
		res.push_back(getAnswer(vec[i]));
	return 0;
}