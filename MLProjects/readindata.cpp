
#include "readindata.h"

using namespace std;

readindata::readindata(string datacon)
{
	ifstream myfile (datacon);
	if(!myfile){  
		cout << "Unable to open myfile";  
        exit(1); // terminate with error  
	}  
	string dataAddr;
	myfile>>dataAddr;          //read in data address
	myfile>>numOfAttr;         //read in num of attributes
	
	
    //read in attribute names
	string attr;
	myfile>>attr;              
	stringstream s(attr);
    string t;         
	while(getline(s,t,',')) //把流按分隔符实现分割 
    {
		attrName.push_back(t);
		//cout<<t<<endl; 
	}
	
	myfile>>targetAttr;
	//cout<<targetAttr;
	for(int i=0;i<numOfAttr ;i++)
	{
		if(i!=targetAttr)remainAttr.push_back(i);
	}


	myfile>>numOfTuple;
	vector<string>* x;
	while(getline(myfile,attr)) //按行读取 
	{
		if(attr=="")continue;
		//cout<<attr<<':';
		stringstream a(attr);
		x=new vector<string>();
		while(getline(a,t,',')) //把流按分隔符实现分割 
		{
			x->push_back(t);
			//cout<<t<<' ';
		}
		//cout<<endl;
		attrVal.push_back(*x);
	}

	int n=attrVal[targetAttr].size();
	numOfTar=new int[n];

	for(int i=0;i<n;i++)   numOfTar[i]=0;






	myfile.close();
	/*
	for(int i=0;i<attrVal.size();i++)
	{
		for(int j=0;j<attrVal[i].size();j++)
			cout<<attrVal[i][j]<<' ';
		cout<<endl;
	}*/


	//read in data

	ifstream datafile (dataAddr);
	if(!datafile){  
		cout << "Unable to open datafile";  
        exit(1); // terminate with error  
	}  

	while(getline(datafile,attr)) //按行读取 
	{
		stringstream a(attr);
		x=new vector<string>();
		while(getline(a,t,',')) //把流按分隔符实现分割 
		{
			x->push_back(t);
		}
		count(*x,targetAttr,numOfTar);

		data.push_back(*x);
	}

	/*
	for(int i=0;i<n;i++)cout<<numOfTar[i]<<' ';
	cout<<endl;

	
	int * cts=counts(6);
	for(int i=0;i<attrVal[6].size();i++)cout<<cts[i]<<' ';
	cout<<endl;
	*/
	
}
void readindata::printData(bool t)
{
	cout<<"numOfTuple: "<<numOfTuple<<endl;
	cout<<"numOfAttr: "<<numOfAttr<<endl<<endl;
	cout<<"Attribute value: "<<endl;
	for(int i=0;i<attrName.size();i++)
	{
		if(i==targetAttr) continue;
		cout<<i<<' '<<attrName[i]<<": ";
		for(int j=0;j<attrVal[i].size();j++)
		{
			cout<<attrVal[i][j]<<", ";
		}
		cout<<endl;
	}
	cout<<endl<<"targetAttr is "<<targetAttr<<" : "<<attrName[targetAttr]<<endl;
	for(int i=0;i<attrVal[targetAttr].size();i++)
	{
		cout<<attrVal[targetAttr][i]<<" : "<<numOfTar[i]<<endl;
	}

	cout<<endl<<"remainAttr: ";
	for(int i=0;i<remainAttr.size();i++)
	{  cout<<attrName[remainAttr[i]]<<", ";
	}
	cout<<endl;
	cout<<"Entropy: "<<entropy()<<endl<<endl;

	if(t){
	for(int i=0;i<data.size();i++)
	{
		for(int j=0;j<data[i].size();j++)
			cout<<data[i][j]<<' ';
		cout<<endl;
	}
	}
}


readindata::readindata(){}

void readindata::shuffleData()
{
	random_shuffle(data.begin(), data.end());
}    //randomly shuffle data

void readindata::count(vector<string> t,int attr,int *num)      //count the number of target value
{
	bool a=false;
	//cout<<t[attr]<<endl;
	for(int i=0;i<attrVal[attr].size();i++)
	{
		
		if(t[attr]==attrVal[attr][i]) {num[i]++;a=true;}

	}
	if(!a) {system("pause");
	}
}

int * readindata::counts(int attr)
{
	int n=attrVal[attr].size();
	int *cts=new int[n];

	for(int i=0;i<n;i++)   cts[i]=0;

	for(int i=0;i<numOfTuple;i++)
	{
		vector<string> t=data[i];
		count(t,attr,cts);

	}
	return cts;


}


double readindata::entropy()
{
	double sum=0;
	for(int i=0;i<attrVal[targetAttr].size();i++)
	{
		double n=(double)numOfTar[i]/numOfTuple;
		//cout<<n<<endl;
		if(n==0) continue;
		else sum-=(n*(log(n)/log(2)));
	}
	return sum;

}


vector<readindata> readindata::vsplit(int attr)        
{
	readindata* x;
	vector<readindata> res;
	for(int i=0;i<attrVal[attr].size();i++)
	{
		x=new readindata();
		x->numOfTuple=0;
		x->numOfAttr=numOfAttr;
		x->attrName=attrName;
		x->attrVal=attrVal;
		x->targetAttr=targetAttr;
		int n=attrVal[targetAttr].size();
	    x->numOfTar=new int[n];
	    for(int i=0;i<n;i++)   x->numOfTar[i]=0;

		for(int j=0;j<remainAttr.size();j++)
		{
			if(attr!=remainAttr[j])x->remainAttr.push_back(remainAttr[j]);
		}
		res.push_back(*x);

	}

	for(int i=0;i<numOfTuple;i++)
	{
		
		for(int j=0;j<attrVal[attr].size();j++)
		{
			if(data[i][attr]==attrVal[attr][j])
			{
				res[j].numOfTuple++;
				res[j].count(data[i],targetAttr,res[j].numOfTar);
			}
			
		}

	}

	return res;


}


double readindata::infoGain(int attr)
{
	vector<readindata> vs=vsplit(attr);
	//for(int i=0;i<vs.size();i++)	vs[i].printData();
	double sum=0;
	for(int i=0;i<vs.size();i++)  sum+= ((double)(vs[i].numOfTuple)/(double)numOfTuple)*vs[i].entropy();
	//cout<<"sum = "<<sum<<endl;
	return entropy()-sum;

}


int readindata::bestAttr()
{
	double max=0;
	int maxIn=-1;
	for(int i=0;i<remainAttr.size();i++)
	{
		double x=infoGain(remainAttr[i]);
		if(max<x) 
		{
			max=x;
			maxIn=remainAttr[i];
		}

		//cout<<attrName[remainAttr[i]]<<" : "<<x<<endl;

	}
	return  maxIn;
}


vector<readindata> readindata::split(int attr)
{
	readindata* x;
	vector<readindata> res;
	for(int i=0;i<attrVal[attr].size();i++)
	{
		x=new readindata();
		x->numOfTuple=0;
		x->numOfAttr=numOfAttr;
		x->attrName=attrName;
		x->attrVal=attrVal;
		x->targetAttr=targetAttr;
		int n=attrVal[targetAttr].size();
	    x->numOfTar=new int[n];
	    for(int i=0;i<n;i++)   x->numOfTar[i]=0;

		for(int j=0;j<remainAttr.size();j++)
		{
			if(attr!=remainAttr[j])x->remainAttr.push_back(remainAttr[j]);
		}
		res.push_back(*x);

	}

	for(int i=0;i<numOfTuple;i++)
	{
		
		for(int j=0;j<attrVal[attr].size();j++)
		{
			if(data[i][attr]==attrVal[attr][j])
			{
				res[j].numOfTuple++;
				res[j].count(data[i],targetAttr,res[j].numOfTar);
				res[j].data.push_back(data[i]);
			}
			
		}

	}

	return res;
}