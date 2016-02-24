#ifndef _NODE_H
#define _NODE_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <algorithm>
#include "readindata.h"
using namespace std;

class Node{
public:
	readindata data;
	bool leaf;
	string label;
	int mAttr;
	//vector<int> remainAttr;
	vector<Node*> children;
	
	void printTree(string s,string space="");
	

	
	Node(readindata &dat);
	Node ID3();
	string find(vector<string> t);     //give a tuple, return its approximate    
	bool judge(vector<string> t);
	int err(readindata& x);
	double acc(readindata& x);
	
	int size();
	int  prun(readindata& x);           //use validation set x to prune tree,return error make
};





#endif 