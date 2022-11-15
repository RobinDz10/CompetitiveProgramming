// Freckles (UVa 10034).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <float.h>
#include <iomanip>
#include <bits/stdc++.h> //Uncomment this line when run the program on OJ
using namespace std;

pair<double, double> parse_line(string& str) {
	string temp1 = "", temp2 = "";
	int len = str.length(), breakPoint = -1;
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ')
			temp1 += str[i];
		else {
			breakPoint = i;
			break;
		}
	}
	for (int i = breakPoint + 1; i < len; ++i)
		temp2 += str[i];
	double num1 = stod(temp1), num2 = stod(temp2);
	return { num1, num2 };
}

double getDistance(int i, int j, vector<double>& x_coordinates, vector<double>& y_coordinates) {
	double x1 = x_coordinates[i], x2 = x_coordinates[j], y1 = y_coordinates[i], y2 = y_coordinates[j];
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

double helper(int num_Nodes, vector<double>& x_coordinates, vector<double>& y_coordinates, vector<vector<double>>& distances) {
	vector<bool> visited(110, false);
	vector<int> vec;
	vec.push_back(0);
	visited[0] = true;
	double res = 0;
	while (true) {
		int start, end;
		double tempDistance = DBL_MAX;
		for (int i = 0; i < vec.size(); ++i) {
			int next = vec[i];
			for (int j = 0; j < num_Nodes; ++j) {
				if (visited[j] == false && distances[next][j] < tempDistance) {
					start = next;
					end = j;
					tempDistance = distances[next][j];
				}
			}
		}
		if (tempDistance == DBL_MAX)
			return res;
		vec.push_back(end);
		visited[end] = true;
		res += tempDistance;
	}
}

int main() {
	/*
	// For test locally
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}
	*/

	// For run the program on OJ
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);

	int currLine = 0;
	int num_Cases = stoi(text[currLine]);
	currLine += 2;

	while (num_Cases--) {
		int num_Nodes = stoi(text[currLine++]);
		vector<double> x_coordinates(num_Nodes + 1);
		vector<double> y_coordinates(num_Nodes + 1);
		vector<vector<double>> distances(num_Nodes + 1, vector<double>(num_Nodes + 1));
		for (int i = 0; i < num_Nodes; ++i) {
			pair<double, double> curr = parse_line(text[currLine++]);
			double currX = curr.first, currY = curr.second;
			x_coordinates[i] = currX;
			y_coordinates[i] = currY;
		}
		for (int i = 0; i < num_Nodes; ++i) {
			for (int j = i + 1; j < num_Nodes; ++j) {
				double distance = getDistance(i, j, x_coordinates, y_coordinates);
				distances[i][j] = distance;
				distances[j][i] = distance;
			}
		}
		double res = helper(num_Nodes, x_coordinates, y_coordinates, distances);
		printf("%.2f\n", res);
		cout << endl;
		currLine++;
	}
	return 0;
}