// Fire Stations (UVa 10278).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAXINT 1000000
using namespace std;

vector<int> parse_line(string& str) {
	vector<int> vec;
	int num = 0, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ') {
			num = num * 10 + (str[i] - '0');
			if (i == len - 1) {
				vec.push_back(num);
				break;
			}
		}
		else {
			vec.push_back(num);
			num = 0;
		}
	}
	return vec;
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

	int currLine = 0;
	int num_Cases = stoi(text[currLine]);
	currLine = 2;


	while (num_Cases--) {
		vector<int> vec1 = parse_line(text[currLine++]);
		int num_ExistingFireStation = vec1[0], num_Intersection = vec1[1];

		vector<int> stations(101);
		vector<int> vec2 = parse_line(text[currLine++]);
		int tempNum = 0;
		for (int i = 1; i <= num_ExistingFireStation; ++i)
			stations[i] = vec2[tempNum++];

		vector<vector<int>> weights(501, vector<int>(501));
		for (int i = 1; i <= num_Intersection; ++i) {
			for (int j = 1; j <= num_Intersection; ++j) {
				weights[i][j] = MAXINT;
			}
		}

		while (true) {
			if (currLine >= text.size() || text[currLine] == "") break;
			vector<int> vec3 = parse_line(text[currLine++]);
			int pos1 = vec3[0], pos2 = vec3[1], distance = vec3[2];
			weights[pos1][pos2] = distance;
			weights[pos2][pos1] = distance;
		}

		for (int k = 1; k <= num_Intersection; ++k) {
			for (int i = 1; i <= num_Intersection; ++i) {
				for (int j = 1; j <= num_Intersection; ++j) {
					int totalDistance = weights[i][k] + weights[k][j];
					if (totalDistance < weights[i][j])
						weights[i][j] = totalDistance;
				}
			}
		}

		for (int i = 1; i <= num_Intersection; ++i)
			weights[i][i] = 0;

		int maxShortestDistance = 0;
		vector<int> shortestDistance(501);
		for (int i = 1; i <= num_Intersection; ++i) {
			int distance = MAXINT;
			for (int j = 1; j <= num_ExistingFireStation; ++j) {
				if (weights[i][stations[j]] < distance)
					distance = weights[i][stations[j]];
			}
			shortestDistance[i] = distance;
			if (distance > maxShortestDistance)
				maxShortestDistance = distance;
		}

		int intersection = 1;
		for (int i = num_Intersection; i >= 1; --i) {
			int tempShortestDistance = 0;
			for (int j = 1; j <= num_Intersection; ++j) {
				if (weights[j][i] < shortestDistance[j]) {
					if (tempShortestDistance < weights[j][i])
						tempShortestDistance = weights[j][i];
				}
				else {
					if (tempShortestDistance < shortestDistance[j])
						tempShortestDistance = shortestDistance[j];
				}
			}
			if (tempShortestDistance <= maxShortestDistance) {
				intersection = i;
				maxShortestDistance = tempShortestDistance;
			}
		}
		cout << intersection << endl;
		currLine++;
	}

	return 0;
}