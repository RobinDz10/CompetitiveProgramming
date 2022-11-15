// Pairsumonious Numbers (10202).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h> // Uncomment this line when run the program on OJ
using namespace std;

vector<int> parse_line(string& str) {
	vector<int> level;
	int num = 0;
	bool flag = true;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ' ') {
			if (flag == false)
				num *= -1;
			level.push_back(num);
			num = 0;
			flag = true;
			continue;
		}
		else if (str[i] == '-') {
			flag = false;
			continue;
		}
		else {
			num = num * 10 + (str[i] - '0');
			if (i == str.length() - 1) {
				level.push_back(num);
				break;
			}
		}
	}
	return level;
}

vector<int> getRes(vector<int>& vec) {
	int nums = vec[0];
	swap(vec[0], vec[vec.size() - 1]);
	vec.pop_back();
	sort(vec.begin(), vec.end());
	int size = vec.size();
	vector<int> temp1 = vec;
	vector<int> temp2(nums);
	for (int i = 2; i < size; ++i) {
		if ((temp1[0] - temp1[1] + temp1[i]) % 2) break;
		temp2[1] = (temp1[i] + temp1[0] - temp1[1]) / 2;
		temp2[0] = temp1[0] - temp2[1];
		temp1[0] = INT_MAX;
		temp2[2] = temp1[i] - temp2[1];
		temp1[i] = INT_MAX;
		for (int j = 3; j < nums; ++j) {
			int minVal = INT_MAX;
			for (int k = 0; k < size; ++k)
				if (minVal > temp1[k])
					minVal = temp1[k];
			if (minVal == INT_MAX) break;
			temp2[j] = minVal - temp2[0];
			for (int k = 0; k < j; ++k) {
				if (temp2[k] != INT_MIN); {
					int pos = -1;
					for (int l = 0; l < size; ++l)
						if (temp1[l] == temp2[j] + temp2[k])
							pos = l;
					if (pos == -1) break;
					temp1[pos] = INT_MAX;
				}
			}
		}
	}
	return temp2;
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
	// For online judge
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);
	*/


	for (int i = 0; i < text.size(); ++i) {
		vector<int> currLine = parse_line(text[i]);
		vector<int> res = getRes(currLine);
		if (res.size() == 0)
			cout << "Impossible!";
		else {
			for (int i = 0; i < res.size(); ++i)
				cout << res[i] << " ";
		}
		cout << endl;
	}
	return 0;
}