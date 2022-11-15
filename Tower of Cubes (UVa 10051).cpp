// Tower of Cubes (UVa 10051).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h> //Uncomment this line when run the program on OJ
using namespace std;

vector<int> parse_line(string& str) {
	vector<int> vec;
	int num = 0, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ') {
			num = num * 10 + (str[i] - '0');
			if (i == len - 1)
				vec.push_back(num);
		}
		else {
			vec.push_back(num);
			num = 0;
		}
	}
	return vec;
}

void printPath(int x, int y, int curr_level, vector<string>& faces, vector<vector<vector<int>>>& cubeArrangement) {
	if (curr_level == 0) return;
	cout << x << " " << faces[y] << endl;
	printPath(cubeArrangement[x][y][0], cubeArrangement[x][y][1], curr_level - 1, faces, cubeArrangement);
}

int main() {
	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			if (line == "") continue;
			text.push_back(line);
		}
		myFile.close();
	}
	
	/*
	// For run the program on OJ
	string line;
	vector<string> text;
	while (getline(cin, line)){
		if(line == "") continue;
		text.push_back(line);
	}
	*/

	vector<string> faces = { "front", "back", "left", "right", "top", "bottom" };
	int currCase = 1;
	int currLine = 0;
	while (currLine < text.size()) {
		int num_cubes = stoi(text[currLine++]);
		if (num_cubes == 0) break;
		cout << "Case #" << currCase << endl;
		currCase++;
		vector<vector<int>> cubes(num_cubes + 1);
		// For each cube:
		//		cube[0] -> front color
		//		cube[1] -> back color
		//		cube[2] -> left color
		//		cube[3] -> right color
		//		cube[4] -> top color
		//		cube[5] -> bottom color
		int pos = 1;
		for (int i = currLine; i < currLine + num_cubes; ++i) {
			vector<int> curr_cube = parse_line(text[i]);
			cubes[pos++] = curr_cube;
		}
		currLine += num_cubes;
		/*currLine++;*/
		vector<vector<int>> dp(num_cubes + 10, vector<int>(6));
		vector<vector<vector<int>>> cubeArrangement(num_cubes + 10, vector<vector<int>>(num_cubes + 10, vector<int>(6)));
		for (int i = 0; i < 6; ++i)
			dp[num_cubes][i] = 1;
		int temp_i = -1, temp_j = -1, max_height = 0, x = 0, y = 0;
		for (int i = num_cubes - 1; i >= 1; --i) {
			for (int j = 0; j < 6; ++j) {
				dp[i][j] = 1;
				for (int k = i + 1; k <= num_cubes; ++k) {
					for (int l = 0; l < 6; ++l) {
						int pos = (j % 2 == 0 ? j + 1 : j - 1);
						if (cubes[i][pos] == cubes[k][l] && dp[i][j] < dp[k][l] + 1) {
							dp[i][j] = dp[k][l] + 1;
							temp_i = k;
							temp_j = l;
						}
					}
				}
				cubeArrangement[i][j][0] = temp_i;
				cubeArrangement[i][j][1] = temp_j;
				if (max_height < dp[i][j]) {
					max_height = dp[i][j];
					x = i;
					y = j;
				}
			}
		}
		cout << max_height << endl;
		printPath(x, y, max_height, faces, cubeArrangement);
		cout << endl;
	}
	return 0;
}