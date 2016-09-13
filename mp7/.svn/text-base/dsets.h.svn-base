/* Your code here! */
#ifndef dsets_h
#define dsets_h

#include <iostream>
#include <vector>

using namespace std;

class DisjointSets{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion(int a, int b);
	private:
		vector<int> nodes;
		//private helper function
		void combine(int root1, int root2, int size);
		bool isBigger(int a, int b);
};

#endif