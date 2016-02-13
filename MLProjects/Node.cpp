#include "Node.h"






Node::Node(readindata &dat)
{

	data=&dat;
	leaf=false;
	//cout<<data->targetAttr<<endl;

	/*
	vector<vector<string>> d=dat.getData();

	vector<string> x;
	targetAttr=dat.targetA();

	int n=(dat.attrV())[targetAttr].size();
	cout<<n;

	numOfTar=new int[n];   
	for(int i=0;i<n;i++)  numOfTar[i]=0;



	for(int i=0;i<d.size();i++)
	{
		x=d[i];
		//x[targetAttr]

		//cout<<x[0]<<endl;
		data.push_back(x);

		
	}
	*/
}


Node Node::ID3()
{
	int maxTar=0;
	int maxIn=0;
	
	//cout<<data->targetA()<<endl;
	for(int i=0;i<((data->attrVal)[data->targetAttr]).size();i++)
	{
		if(data->numOfTar[i]>maxTar) 
		{
			maxTar=data->numOfTar[i];
			maxIn=i;
		}

		if(data->numOfTar[i]==data->numOfTuple)
		{
			leaf=true;
			label=data->attrVal[data->targetAttr][i];
			return *this;
		}
	}

	//cout<<data->attrVal[data->targetAttr][maxIn];

	if(data->remainAttr.empty()) 
	{
		leaf=true;
		label=data->attrVal[data->targetAttr][maxIn];
	}
	
	//for every remain attributes, compute their information gain

	return *this;


}
