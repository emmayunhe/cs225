/* Your code here! */
#include "dsets.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


//addelements
//creates n unconnected root nodes at the end of the vector
void DisjointSets::addelements(int num){
	for(int i=0; i<num; i++){
		nodes.push_back(-1);
	}
}

//find
//returns the root of the up-tree in which the parameter elements resides
int DisjointSets::find(int elem){
	if(nodes[elem] < 0){
		return elem;
	}
	int ret = find(nodes[elem]);
	nodes[elem] = ret;
	return ret;
}

//setunion
//combine two trees in which the two elements resides
void DisjointSets::setunion(int a, int b){
	int root1 = find(a);
	int root2 = find(b);
	if(root1 != root2){
		int size = nodes[root1]+nodes[root2];
		if(isBigger(nodes[root1], nodes[root2])){
			nodes[root2] = root1;
			nodes[root1] = size;
		}
		else{
			nodes[root1] = root2;
			nodes[root2] = size;
		}
	}
}

//isBigger
//helper function for combine
bool DisjointSets::isBigger(int a, int b){
	return (a <= b);
}