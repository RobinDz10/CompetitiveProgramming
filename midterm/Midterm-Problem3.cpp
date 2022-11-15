// Midterm-Problem3.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string addNum(string& str1, string& str2) {
	string temp1 = str1, temp2 = str2, res = "";
	reverse(temp1.begin(), temp1.end());
	reverse(temp2.begin(), temp2.end());
	int len1 = temp1.length(), len2 = temp2.length(), flag = 0, len;
	if (len1 > len2) {
		for (int i = 0; i < (len1 - len2); ++i)
			temp2 += '0';
	}
	else {
		for (int i = 0; i < (len2 - len1); ++i)
			temp1 += '0';
	}
	len = temp1.length();
	for (int i = 0; i < len; ++i) {
		int digit1 = temp1[i] - '0', digit2 = temp2[i] - '0';
		if (flag == 0) {
			if (digit1 + digit2 < 10)
				res += to_string(digit1 + digit2);
			else {
				res += to_string(digit1 + digit2 - 10);
				flag = 1;
			}
		}
		else {
			if (digit1 + digit2 + 1 < 10) {
				res += to_string(digit1 + digit2 + 1);
				flag = 0;
			}
			else
				res += to_string(digit1 + digit2 + 1 - 10);
		}
	}
	if (flag == 1) res += '1';
	reverse(res.begin(), res.end());
	return res;
}

string mulNum(string& str1, string& str2) {
	if (str1 == "0" || str2 == "0") return "0";
	int len1 = str1.length(), len2 = str2.length();
	vector<int> res(len1 + len2, 0);
	for (int i = len1 - 1; i >= 0; --i) {
		for (int j = len2 - 1; j >= 0; --j) {
			res[i + j + 1] += (str1[i] - '0') * (str2[j] - '0');
			res[i + j] += res[i + j + 1] / 10;
			res[i + j + 1] %= 10;
		}
	}
	int i = 0;
	string str = "";
	while (res[i] == 0)
		i++;
	while (i < res.size())
		str += to_string(res[i++]);
	return str;
}

string getNumber(vector<int>& letter, vector<int>& alphabet) {
	if (letter.size() == 0)
		return "0";
	int size = letter.size(), len = alphabet.size();
	if (letter[0] == alphabet[0]) {
		letter.erase(letter.begin());
		alphabet.erase(alphabet.begin());
		return getNumber(letter, alphabet);
	}
	int start = letter[0];
	letter.erase(letter.begin());
	int index = 0;
	for (int i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] == start) {
			index = i;
			alphabet.erase(alphabet.begin() + i);
			break;
		}
	}
	string res = to_string(index);
	for (int i = len - size + 1; i < len; i++) {
		string temp1 = to_string(i);
		string temp2 = mulNum(res, temp1);
		res = temp2;
	}
	string next = getNumber(letter, alphabet);
	return addNum(res, next);
}

int main() {
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}

	int num_cases = stoi(text[0]), currLine = 1;
	for (int i = 0; i < num_cases; ++i) {
		string curr = text[currLine++];
		vector<int> letter;
		vector<int> alphabet;
		for (int j = 0; j < curr.length(); ++j) {
			char ch = curr[j];
			letter.push_back(ch - 'A');
		}
		for (int j = 0; j < 26; ++j)
			alphabet.push_back(j);
		cout << getNumber(letter, alphabet) << endl;
	}	
	return 0;
}