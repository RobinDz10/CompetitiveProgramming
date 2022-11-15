// Ones (10127).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h> // Uncomment this line when run the program on online judge
using namespace std;

void getRes(int& curr, vector<int>& res) {
	int ans = 0, num = 1;
	while (true) {
		if (num % curr == 0) break;
		num = (num * 10 + 1) % curr;
		ans++;
	}
	res.push_back(ans);
}

int main() {
	/*
	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<int> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(stoi(line));
		myFile.close();
	}
	*/

	// For online judge
	string line;
	vector<int> text;
	while (getline(cin, line))
		text.push_back(stoi(line));

	vector<int> res;
	for (int i = 0; i < text.size(); ++i)
		getRes(text[i], res);
	for (int i = 0; i < res.size(); ++i)
		cout << res[i] + 1 << endl;
	return 0;
}