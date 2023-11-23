#pragma once
#include <set>
using namespace std;
class Solutions
{
public:
	void FromGod(int** a, int n);
    set<int> Greedy(int** a, int n);
    void Generator();
	void Print(int** a, int n);
	void FromFile(int** a, int n);
	void FromKeybord(int** a, int n);
	
};