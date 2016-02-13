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
	readindata* data;
	bool leaf;
	string label;
	string attrName;
	vector<int> remainAttr;
	vector<Node*> children;
	
	
	

	
	Node(readindata &dat);
	Node ID3();
	

};





#endif 