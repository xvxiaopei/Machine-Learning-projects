#include<iostream>
#include<fstream>
#include<vector>
#include "readindata.h"
#include "Node.h"

using namespace std;

int main(){
	readindata a("./data/car/dataConforCar.txt");
	//a.shuffleData();
	//a.printData();
	//cout<<a.targetA()<<endl;

	Node x(a);
	//cout<<a.targetA()<<endl;
	//x.ID3();
	//cout<<x.data->entropy();
	//x.printData();


	//cout<<a.bestAttr();
	vector<readindata> mm=a.split(5);
	mm[2].printData(true);
	//cout<<a.infoGain(0);
	

	
	cout<<"Hello world!";
	
}