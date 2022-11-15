// Factovisors (UVa 10139).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
//#include <bits/stdc++.h> //Uncomment this line when run the program on OJ
using namespace std;

pair<int, int> parse_line(string& str) {
	int first = 0, second = 0, breakPoint = -1, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ')
			first = first * 10 + (str[i] - '0');
		else {
			breakPoint = i;
			break;
		}
	}
	for (int i = breakPoint + 1; i < len; ++i)
		second = second * 10 + (str[i] - '0');
	return { first, second };
}

int getGCD(int num1, int num2) {
    if (num2 == 0) return num1;
    return getGCD(num2, num1 % num2);
}

bool isPrime(int num) {
    if (num == 1) return false;
    int temp = (int)sqrt(num);
    for (int i = 2; i <= temp; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}

bool helper(int& n, int& m, bool& canDivide) {
    int temp = m;
    for (int i = n; i >= 2; --i) {
        int gcd = getGCD(temp, i);
        if (gcd > 1) {
            temp /= gcd;
            if (temp < i) {
                canDivide = true;
                break;
            }
            if (isPrime(temp)) {
                canDivide = false;
                break;
            }
        }
    }
    return canDivide;
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
    
    for (int i = 0; i < text.size(); ++i) {
        pair<int, int> curr = parse_line(text[i]);
        int n = curr.first, m = curr.second;
        //cout << n << " " << m << endl;
        if (m == 0 || (isPrime(m) && m > n)) {
            cout << m << " does not divide " << n << "!" << endl;
            continue;
        }
        if (m == 1 || m <= n) {
            cout << m << " divides " << n << "!" << endl;
            continue;
        }
        bool canDivide = false;
        if(helper(n, m, canDivide))
            cout << m << " divides " << n << "!" << endl;
        else
            cout << m << " does not divide " << n << "!" << endl;
    }
    return 0;
}