// Midterm-Problem1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int helper(vector<int>& res, vector<int>& av, int end, int t, int count) {
	if (t <= 0) {
		if (res[0] > 0 || t > res[0] || (t == res[0] && count < res[1])) {
			res[0] = t;
			res[1] = count;
		}
		return 0;
	}
	if (res[0] == 0 && res[1] <= count)
		return 0;
	if (end >= 0) {
		helper(res, av, end - 1, t - av[end], count + 1);
		helper(res, av, end - 1, t, count);
	}
	return 0;
}

int main() {
	fstream myFile("Input.txt");
	string line;
	vector<int> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(stoi(line));
		myFile.close();
	}

	int num_cases = text[0], currLine = 1, t, n, ai;
	vector<int> res;
	res.push_back(1);
	res.push_back(0);
	for (int i = 0; i < num_cases; ++i) {
		t = text[currLine++];
		n = text[currLine++];
		vector<int> av;
		res[0] = 1;
		for (int j = 0; j < n; ++j) {
			ai = text[currLine + j];
			av.push_back(ai);
		}
		sort(av.begin(), av.end());
		helper(res, av, av.size() - 1, t, 0);
		cout << t - res[0] << " " << res[1] << endl;
		currLine += n;
	}
	return 0;
}