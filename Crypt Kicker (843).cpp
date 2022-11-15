#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

/* Func to get all words in a single level */
vector<string> parse_line(string& textLine) {
	vector<string> ans;
	string str = "";
	for (int i = 0; i < textLine.size(); ++i) {
		if (textLine[i] == ' ') {
			ans.push_back(str);
			str = "";
		}
		else {
			str += textLine[i];
			if (i == textLine.size() - 1) {
				ans.push_back(str);
				break;
			}
		}
	}
	return ans;
}

/* Reset the level_output if needed */
void reset(vector<string>& level_output, vector<string>& level_words) {
	level_output.clear();
	for (int i = 0; i < level_words.size(); ++i) {
		int currLength = level_words[i].length();
		string str = "";
		for (int j = 0; j < currLength; ++j)
			str += '*';
		level_output.push_back(str);
	}
}

bool isMatch(string& word1, string& word2, vector<char>& matches1, vector<char>& matches2) {
	if (word1.length() != word2.length()) return false;
	vector<char> temp1 = matches1, temp2 = matches2;
	for (int i = 0; i < word1.length(); ++i) {
		char ch1 = word1[i], ch2 = word2[i];
		if (temp1[ch1 - 'a'] == ' ' && temp2[ch2 - 'a'] == ' ') {
			temp1[ch1 - 'a'] = ch2;
			temp2[ch2 - 'a'] = ch1;
			continue;
		}
		else if (temp1[ch1 - 'a'] == ch2 && temp2[ch2 - 'a'] == ch1)
			continue;
		else
			return false;
	}
	return true;
}

void updateMatches(string& word1, string& word2, vector<char>& matches1, vector<char>& matches2) {
	for (int i = 0; i < word1.length(); ++i) {
		char ch1 = word1[i], ch2 = word2[i];
		matches1[ch1 - 'a'] = ch2;
		matches2[ch2 - 'a'] = ch1;
	}
	return;
}

/* Still have little problems in this section, other sections are good, but deadline is coming, I have to submit it before due date */
vector<string> dfs(vector<string>& dictionary, vector<string>& level_words, vector<string>& level_output, vector<char>& matches1, vector<char>& matches2, int pos_dict, int pos_level_words) {
	if (level_output.size() == level_words.size())
		return level_output;
	/*if (pos_level_words < 0) {
		reset(level_output, level_words);
		return level_output;
	}*/
	vector<char> tempMatches1 = matches1;
	vector<char> tempMatches2 = matches2;
	string curr_dict_word = dictionary[pos_dict];
	string curr_level_word = level_words[pos_level_words];
	int tempPos = pos_dict;
	if (isMatch(curr_dict_word, curr_level_word, matches1, matches2)) {
		/*cout << "Match!" << endl;*/
		updateMatches(curr_dict_word, curr_level_word, matches1, matches2);
		pos_dict = 0;
		pos_level_words++;
		level_output.push_back(curr_dict_word);
		return dfs(dictionary, level_words, level_output, matches1, matches2, pos_dict, pos_level_words);
	}
	else {
		if (pos_dict < dictionary.size() - 1) {
			/*cout << "NOT match! Continue looking for possible dict word" << endl;*/
			pos_dict++;
			return dfs(dictionary, level_words, level_output, matches1, matches2, pos_dict, pos_level_words);
		}
		else {
			/*cout << "NOT match! back Track" << endl;*/
			matches1 = tempMatches1;
			matches2 = tempMatches2;
			pos_level_words--;
			if (pos_level_words < 0) {
				reset(level_output, level_words);
				return level_output;
			}
			level_output.pop_back();
			/* Here is the problem that I still need to think */
			return dfs(dictionary, level_words, level_output, matches1, matches2, tempPos + 1, pos_level_words);
		}
	}
}

vector<string> helper(vector<string>& dictionary, vector<string>& level_words) {
	vector<string> level_res;
	vector<char> matches1(26, ' '); // Projection from dictionary to level_words
	vector<char> matches2(26, ' '); // Projection from level_words to dictionary
	//vector<string> ans = dfs(dictionary, level_words, level_res, matches1, matches2, 0);
	vector<string> ans = dfs(dictionary, level_words, level_res, matches1, matches2, 0, 0);
	return ans;
}

int main() {
	// For test in local machine
	fstream myFile("Input.txt");
	vector<string> text;
	string line;
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			text.push_back(line);
		}
		myFile.close();
	}

	/*
	// For test online
	vector<string> text;
	string line;
	while (getline(cin, line)) {
		text.push_back(line);
	}
	*/

	// Main Program
	vector<vector<string>> res;
	int num_dict_words = stoi(text[0]);

	// Create the dictionary
	vector<string> dictionary;
	for (int i = 1; i <= num_dict_words; ++i)
		dictionary.push_back(text[i]);
	
	for (int i = num_dict_words + 1; i < text.size(); ++i) {
		vector<string> level_words = parse_line(text[i]);
		vector<string> level_output = helper(dictionary, level_words);
		res.push_back(level_output);
	}

	// Standard output
	for (int i = 0; i < res.size(); ++i) {
		for (int j = 0; j < res[i].size() - 1; ++j)
			cout << res[i][j] << " ";
		cout << res[i][res[i].size() - 1] << endl;
	}
	return 0;
}