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
    vector<int> NFIDs;
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

structPolicyList gen_PolicyList(const char* FILE_NAME, structPolicyList PolicyList){

	ifstream fileread (FILE_NAME);
	string line;

	while(getline(fileread,line)){
		istringstream iss(line);
		vector<string> tokens;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));

		Policy NewPolicy;

		stringstream s1;
		int c1;
		s1 << tokens[0];
		s1 >> c1;
		NewPolicy.index = c1;

		stringstream s;
		char c;
		s << tokens[1];
		s >> c;
		NewPolicy.AR = c;

		stringstream s11;
		int c11;
		s11 << tokens[2];
		s11 >> c11;
		NewPolicy.PolicyID = c11;

		NewPolicy.CustomerID = tokens[3];
		NewPolicy.src_dst = tokens[4];

		for(size_t i=5;i<tokens.size();i++){
			stringstream ss;
			int cc;
			ss << tokens[i];
			ss >> cc;
			NewPolicy.NFIDs.push_back(cc);
		}

		PolicyList.PolicyList.push_back(NewPolicy);
	}

	return PolicyList;
}

void PrintNewPolicyList(Policy OriginalPolicy, int BWPerPolicy){ 
	ofstream myfile;
    myfile.open ("Policy10.txt", ios::out | ios::app);

	myfile << OriginalPolicy.index<< " ";
	myfile << OriginalPolicy.AR << " ";
	myfile << OriginalPolicy.PolicyID<< " ";
	myfile << OriginalPolicy.CustomerID << " ";
	myfile << BWPerPolicy << " ";
	myfile << OriginalPolicy.src_dst << " ";

	for(int j=0; j<OriginalPolicy.NFIDs.size();j++){
		myfile << OriginalPolicy.NFIDs[j] << " ";
	}

	myfile << "\n";
	
	myfile.close();
}

int main (){

	int NoOfCustomers = 4;

	structPolicyList OriginalPolicyList = gen_PolicyList("OriginalPolicy10.txt", OriginalPolicyList);
	vector<Customer> Customers = gen_customerList("Customers.txt");

	int NoOfPolicies = 0;
	int CustomerID = 0;
	vector<int> PoliciesPerCustomers;

	for( int i = 0; i < OriginalPolicyList.PolicyList.size(); i++){
		if( !(i == OriginalPolicyList.PolicyList.size() - 1)){
			if(OriginalPolicyList.PolicyList[i].CustomerID.compare(OriginalPolicyList.PolicyList[i+1].CustomerID) == 0){
				NoOfPolicies ++;
			}
			else{
				NoOfPolicies ++;
				PoliciesPerCustomers.push_back(NoOfPolicies);
				NoOfPolicies = 0;
			}
		}
		else{
			NoOfPolicies ++;
			PoliciesPerCustomers.push_back(NoOfPolicies);
		}
	}

	vector<int> BWPerCustomer;
	for(int j = 0; j< Customers.size(); j++){
		string BWForCustomer = Customers[j].BW;
		stringstream ss;
		int bw;
		ss << BWForCustomer;
		ss >> bw;

		int BWPerPolicy = bw / PoliciesPerCustomers[j];
		BWPerCustomer.push_back(BWPerPolicy);
	}

	int PolicyCount = 0;
	for(int h = 0; h< Customers.size(); h++){
		for(int f=0; f< PoliciesPerCustomers[h]; f++){
			int NowBW = BWPerCustomer[h];
			PrintNewPolicyList(OriginalPolicyList.PolicyList[PolicyCount], NowBW);
			PolicyCount ++;
		}
	}


	return 0;
}