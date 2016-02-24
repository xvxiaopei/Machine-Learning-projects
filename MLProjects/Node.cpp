#include "Node.h"






Node::Node(readindata &dat)
{

	data=dat;
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
	//cout<<"?"<<endl;
	for(int i=0;i<((data.attrVal)[data.targetAttr]).size();i++)
	{	
		if(data.numOfTar[i]>maxTar) 
		{
			maxTar=data.numOfTar[i];
			maxIn=i;
		}

		if(data.numOfTar[i]==data.numOfTuple)
		{
			leaf=true;
			label=data.attrVal[data.targetAttr][i];
			mAttr=data.targetAttr;
			//cout<<label<<endl;
			return *this;
		}
	}
		
	//cout<<data->attrVal[data->targetAttr][maxIn];
	
	if(data.remainAttr.empty()) 
	{
		leaf=true;
		label=data.attrVal[data.targetAttr][maxIn];
		mAttr=data.targetAttr;
		//cout<<label<<endl;
		return *this;
	}
	
	//for every remain attributes, compute their information gain
	
	int A=data.bestAttr();
	
	vector<readindata> mm=(data.split(A));
	//label = data->attrName[A];
	//cout<<"!"<<endl;
	mAttr=A;
	
	//cout<<data.attrName[A]<<endl;
	for(int i=0;i<data.attrVal[A].size();i++)
	{
		
		//cout<<mm.size()<<" "<<data.attrVal[A].size()<<endl;
		children.push_back(new Node((mm)[i]));
		
		if((mm)[i].numOfTuple==0)
		{
			
			//cout<<"!"<<endl;
			children[i]->leaf=true;
			children[i]->label=data.attrVal[data.targetAttr][maxIn];
			//cout<<children[i]->label<<endl;
			children[i]->mAttr=data.targetAttr;
			
		}
		else 
		{
			children[i]->ID3();
		}

	}
	
	return *this;
}

void Node::printTree(string s,string space)
{
	


	if(leaf==true) 
	{
		//cout<<"!?";
		ofstream myfile (s,ofstream::out|ofstream::app);
		if(!myfile){  
		cout << "Unable to open myfile";  
        exit(1); // terminate with error  
		}  
		//cout<<mAttr<<endl;
		myfile<<space<<data.attrName[mAttr]<<" = "<<label<<"  [";
		int i=0;
		
		myfile<<data.numOfTar[i]<<" "<<data.attrVal[data.targetAttr][i]<<" ";
		//myfile<<"!!\n";
		for(i=1;i<data.attrVal[data.targetAttr].size();i++)
		{
			myfile<<','<<data.numOfTar[i]<<" "<<data.attrVal[data.targetAttr][i]<<" ";
		}
		myfile<<"]\n";
		myfile.close();
	}
	else
	{
		
		//data.printData();
		//cout<<mAttr<<endl;
		
		//cout<<a<<endl;
		
		
		//system ("PAUSE");
		//cout<<data->attrName.size()<<endl;
		//data.printData();
		//if(data.attrName.size()<5) system ("PAUSE");
		
		for(int i=0;i<children.size();i++)
		{
			
			ofstream myfile (s,ofstream::out|ofstream::app);
			if(!myfile){  
				cout << "Unable to open myfile";  
				exit(1); // terminate with error  
			}  
			
			myfile<<space<<data.attrName[mAttr]<<" = "<<data.attrVal[mAttr][i]<<"  [";
			int j=0;
			myfile<<data.numOfTar[j]<<" "<<data.attrVal[data.targetAttr][j]<<" ";
			for(j=1;j<data.attrVal[data.targetAttr].size();j++)
			{
			myfile<<','<<data.numOfTar[j]<<" "<<data.attrVal[data.targetAttr][j]<<" ";
			}
			myfile<<"]\n";
			
			myfile.close();
			
			children[i]->printTree(s,space+"  ");
		}
	}
	
}


string Node::find(vector<string> t)
{
	if(leaf) return label;
	for(int i=0;i<data.attrVal[mAttr].size();i++)
	{
		if(t[mAttr]==data.attrVal[mAttr][i]) 
		{
			return children[i]->find(t);
		}
	}
	return "?!?";

}

bool Node::judge(vector<string> t)
{
	return (t[data.targetAttr]==find(t));
}

int Node::err(readindata& x)
{
	int r=0;
	for(int i=0;i<x.data.size();i++)
	{
		/*
		for(int j=0;j<x.data[i].size();j++)
			cout<<x.data[i][j]<<" ";
		cout<<" : ";
		cout<<find(x.data[i])<<endl;
		*/
		if(!judge(x.data[i]))r++;
	}
	return r;
}

double Node::acc(readindata& x)
{
	return 1.0-(double(err(x))/x.data.size());
}

int Node::prun(readindata& x)
{
	//double ac=acc(x);

	if(leaf) return err(x);
	//int er=err(x);

	int ner=0;
	vector<readindata> sData=x.split(mAttr);
	for(int i=0;i<children.size();i++)
	{
		ner+=children[i]->prun(sData[i]);
	}
	for(int i=0;i<children.size();i++)
	{
		if(!(children[i]->leaf)) return err(x);
	}


	int mTarVal=0;
	int numTarVal=0;
	for(int i=0;i<x.attrVal[x.targetAttr].size();i++)
	{
		if(x.numOfTar[i]>numTarVal) 
		{
			numTarVal=x.numOfTar[i];
			mTarVal=i;
		}

		//cout<<x.attrVal[x.targetAttr][i]<<" : "<<x.numOfTar[i]<<"  ";

	}
	/*
	cout<<endl<<"Majority: "<<x.attrVal[x.targetAttr][mTarVal]<<"  "<<numTarVal<<endl;
	cout<<"leaf estimate error: "<<x.numOfTuple-numTarVal<<endl;
	cout<<"fact error: "<<ner<<endl;
	*/
	if(x.numOfTuple-numTarVal<=ner)            //prune
	{
		leaf=true;
		label=x.attrVal[x.targetAttr][mTarVal];
		mAttr=x.targetAttr;
		return x.numOfTuple-numTarVal;
	}
	else return ner;     //not prune



	//if(leaf) return (er<x.numOfTuple-numTarVal)?er:(x.numOfTuple-numTarVal);

	



}

int Node::size()
{
	int s=1;
	if(!leaf)
	{
		for(int i=0;i<children.size();i++)
			s+=children[i]->size();
	}
	return s;
}