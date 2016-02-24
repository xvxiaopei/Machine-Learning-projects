#include<iostream>

#include<vector>
#include "readindata.h"
#include "Node.h"

using namespace std;



Node decisionT(string conFile,string out)
{
	ofstream myfile (out);
	myfile<<"Read in Control File from: "<<conFile<<endl;
	readindata a(conFile);
	myfile<<"Complete!"<<endl;
	
	srand(time(0));
	
	a.shuffleData();

	int majorC=0;
	int max=0;
	int sizebefore=0;
	int sizeafter=0;

	for(int i=0;i<a.attrVal[a.targetAttr].size();i++)
	{
		if(a.numOfTar[i]>max) 
		{
			max=a.numOfTar[i];
			majorC=i;
		}

		//cout<<x.attrVal[x.targetAttr][i]<<" : "<<x.numOfTar[i]<<"  ";

	}

	for(int i=0;i<10;i++){         //ten fold

		cout<<i<<endl;
	vector<readindata> div=a.divide(i);
	//for(int i=0;i<div.size();i++)  div[i].printData();
	myfile<<i<<" th fold------------------------------------------------------\n";

	
	myfile<<"Construct Decision Tree:";

	//a.printData();

	Node x(div[0]);
	x.ID3();
	myfile<<"Complete!\n";
	//cout<<"?";
	readindata majorClass=div[2].split(a.targetAttr)[majorC];  //set of instance with major classifier 
	myfile<<"Accurancy : "<<x.acc(div[2])<<'\n';
	myfile<<"Major Classifier Accurancy : "<<x.acc(majorClass)<<'\n';
	cout<<x.size();
	sizebefore+=x.size();

	x.prun(div[1]);
	sizeafter+=x.size();
	cout<<' '<<x.size()<<endl;
	myfile<<"After pruning : "<<'\n';
	myfile<<"Accurancy after pruning : "<<x.acc(div[2])<<"\n";
	myfile<<"Major Classifier Accurancy : "<<x.acc(majorClass)<<"\n\n\n";
	}
	Node x(a);

	cout<<endl<<"size p:"<<(double)sizeafter/(double)sizebefore<<endl;

	//myfile<<"\n\n\nPrint Tree Node:\n\n\n";
	myfile.close();
	return x;

}



int main(){


	
	//string in="./data/balance_scale/dataConforBS.txt";
	//string out="./data/balance_scale/output3.txt";

	//string in="./data/car/dataConforCar.txt";
	//string out="./data/car/output.txt";

	//string in="./data/nursery/dataConforNur.txt";
	//string out="./data/nursery/output2.txt";

	string in="./data/blog/dataConforBlog.txt";
	string out="./data/blog/output3.txt";

	//string in="./data/mush/dataConforMsh.txt";
	//string out="./data/mush/output2.txt";

	//string in="./data/vote/dataConforVote.txt";
	//string out="./data/vote/output3.txt";

	Node x=decisionT(in,out);


	/*
	ofstream myfile (out);

	myfile<<"Print Tree Node:\n\n\n";
	myfile.close();
	x.printTree(out);
	*/
	
	



	

	

	cout<<"Hello world!";
	
}