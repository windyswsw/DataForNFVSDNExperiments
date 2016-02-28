/*
 * Test.cpp
 *
 *  Created on: 15 May 2014
 *      Author: Windhya Rankothge
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>
#include <cmath>
#include <math.h>

using namespace std;

struct Policy{
    vector<string> ServiceName;
	int PolicyID;
	string src_dst;
	string AR;
	string CustomerID;
	int index;
};

struct structPolicyList{
	vector<Policy> PolicyList;
};

struct Customer{
	string CustomerID;
	string BW;
};

std::vector<string> gen_IPList(const char* FILE_NAME){
	vector<string> IPList;

	ifstream fileread (FILE_NAME);
	string line;

	while(getline(fileread,line)){
		IPList.push_back(line);
	}

	return IPList;
}

std::vector<Customer> gen_customerList(const char* FILE_NAME){
	vector<Customer> customerList;

	ifstream fileread (FILE_NAME);
	string line;

	while(getline(fileread,line)){
		istringstream iss(line);
		vector<string> tokens;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));

		Customer C;
		C.CustomerID = tokens[0];
		C.BW = tokens[1];

		customerList.push_back(C);
	}
	return customerList;
}

void printFullList(vector<Policy> newstructPolicyList, string BW){
	ofstream myfile;
    myfile.open ("OriginalPolicy10.txt", ios::out | ios::app);

	for(int i=0; i<newstructPolicyList.size();i++){
		myfile << newstructPolicyList[i].index<< " ";
		myfile << newstructPolicyList[i].AR << " ";
		myfile << newstructPolicyList[i].PolicyID<< " ";
		myfile << newstructPolicyList[i].CustomerID << " ";
		myfile << newstructPolicyList[i].src_dst << " ";

		for(int j=0; j<newstructPolicyList[i].ServiceName.size();j++){
			myfile << newstructPolicyList[i].ServiceName[j] << " ";
		}

		myfile << "\n";
	}
	myfile.close();
}

int TruncatedFunc(int m, int M, float p) {
	double r =(rand()*1.0)/(RAND_MAX*1.0);
    double nexp=p+1.0;
	double p1 = ((pow(M*1.0,nexp)-pow(m*1.0,nexp))*r + pow(m*1.0,nexp));
	double p2 = 1.0/nexp;
	double p3 = pow(p1,p2);
	return (int)floor(p3);
}

int main (){

	int min = 2; // minimum no. of NFs per policy
	int max = 7; // maximum no. of NFs per policy
	float p = 2; // truncated power-low distribution with exponent 2
	int NoOfCustomers = 4;
	int TotNoOfServices = 100; // total no. of NFs per customer

	srand((unsigned int) time(0));

	vector<int> PolicyIDList;

	for(int c=200; c>0; c--){
		PolicyIDList.push_back(c);
	}

	int index = 0;

	for(int g = 0; g < NoOfCustomers; g++){

		int NoOfServices = 0;

		structPolicyList newstructPolicyList;

		vector<string> IPs = gen_IPList("IPs.txt");
		vector<Customer> Customers = gen_customerList("Customers.txt");
		vector<string> Services = gen_IPList("Services.txt");

		string BW = Customers[g].BW;

		vector<int> MiddleBoxIDList;

		for(int m=100; m>0; m--){ // 100 middleboxes
			MiddleBoxIDList.push_back(m);
		}

		// according to the study, IP Firewalls: 46, so m=0 to 46, IP Firewalls
		// according to the study, Application firewalls: 9, so m=47 to 55, Application firewalls etc....

		int tot = 0;

		vector<int> numbers(50);
		for(int i=0 ; i<50 ; i++) {
			numbers[i]=TruncatedFunc(min, max, p); // create 50 random numbers from truncated function to decide how many NFs per policy ( each number represents no.of NFs in a policy)
		}

		while(TotNoOfServices > NoOfServices){

			Policy myPolicy;
			vector<string> ServiceName;

			myPolicy.index = index + 1;

			myPolicy.AR = "A";
		
			string src = IPs.back();
			IPs.pop_back();
			string dst = IPs.back();
			IPs.pop_back();
			string strdst = src + "-" + dst;
			myPolicy.src_dst = strdst;

			myPolicy.PolicyID = PolicyIDList.back();
			PolicyIDList.pop_back();

			myPolicy.CustomerID = Customers[g].CustomerID;

			//int ns = rand() % maxNoOfServices + 2;
			int ns = numbers.back();
			numbers.pop_back();

			int mbPos = 0;
			int mb = 0;
			int l = 0;

			for(int i=0; i<ns; i++){
				if(TotNoOfServices > NoOfServices){
					mbPos = rand() % MiddleBoxIDList.size();
					mb = MiddleBoxIDList[mbPos];
					swap(MiddleBoxIDList[mbPos], MiddleBoxIDList.back());
					MiddleBoxIDList.pop_back();

					// according to the study, IP Firewalls: 46, so m=0 to 46, IP Firewalls ( l = 6)
					// according to the study, Application firewalls: 9, so m=47 to 55, Application firewalls (l = 0) etc....

					if(mb <= 46 ){
						l = 0;
					}
					else if(mb > 46 && mb <= 55){
						l = 1;
					}
					else if(mb > 55 && mb <= 61){
						l = 2;
					}
					else if(mb > 61 && mb <= 64){
						l = 3;
					}
					else if(mb > 64 && mb <= 70){
						l = 4;
					}
					else if(mb > 70 && mb <= 77){
						l = 5;
					}
					else{
						l = 6;
					}

					NoOfServices = NoOfServices + 1;
					ServiceName.push_back(Services[l]);
				}
			}
			myPolicy.ServiceName = ServiceName;
			newstructPolicyList.PolicyList.push_back(myPolicy);
			index ++;
		}
		printFullList(newstructPolicyList.PolicyList,BW);
	}
	return 0;
}