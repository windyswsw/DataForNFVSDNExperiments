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

using namespace std;

typedef struct{
	int Customer;
    string Op;
    string BW;
} Info;

struct OnePeriod{
	vector<Info> OnePeriodList;
};

struct PolicyNumVectors{
	int Pol;
	vector<int> C1;
	vector<int> C2;
	vector<int> C3;
	vector<int> C4;
	vector<int> C1A;
	vector<int> C2A;
	vector<int> C3A;
	vector<int> C4A;
};

struct AddPolicy{
	vector<int> C1A;
	vector<int> C2A;
	vector<int> C3A;
	vector<int> C4A;
};

struct Policy{
    vector<int> NFIDs;
	int PolicyID;
	string src_dst;
	string AR;
	string CustomerID;
	int index;
	int BW;
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

		stringstream s112;
		int c112;
		s112 << tokens[4];
		s112 >> c112;
		NewPolicy.BW = c112;

		NewPolicy.src_dst = tokens[5];

		for(size_t i=6;i<tokens.size();i++){
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

std::vector<OnePeriod> gen_PeriodicalInfo(const char* FILE_NAME){
	vector<OnePeriod> FullList;

	ifstream fileread (FILE_NAME);
	string line;
	int r =0;

	while(getline(fileread,line)){
		istringstream iss(line);
		vector<string> tokens;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
		
		OnePeriod OnePeriodListObj;

		for(int g=0; g< tokens.size(); g++){

			Info NewInfo;
			vector<string> InfoArr;

			std::string s1 = tokens[g];
			std::string delimiter = "-";
			size_t pos = 0;
			std::string subtoken;
			while ((pos = s1.find(delimiter)) != std::string::npos) {
				subtoken = s1.substr(0, pos);
				InfoArr.push_back(subtoken);
				s1.erase(0, pos + delimiter.length());
			}

			NewInfo.Customer = g;
			NewInfo.Op = InfoArr[0];
			NewInfo.BW = s1;

			OnePeriodListObj.OnePeriodList.push_back(NewInfo);
		}

		FullList.push_back(OnePeriodListObj);
	}
	return FullList;
}

void PrintInFile(int PolicyID, char O, int cus, string BW){

	ofstream myfile;
    myfile.open ("ChangePolicy.txt", ios::out | ios::app);

	if(PolicyID != 0){
		myfile << cus << " ";
		myfile << PolicyID << " ";
		myfile << O << " ";
		myfile << BW ;
	}
	else{
		myfile << cus << " ";
		myfile << PolicyID << " ";
		myfile << 0 << " ";
		myfile << 0 ;
	}
	myfile << "\n";
	myfile.close();
}

PolicyNumVectors getAPolicyNumber(int C, PolicyNumVectors getAPolicyNumberObj, char Op){

	PolicyNumVectors retPolicyNumVectors;
	int size=0;
	int P=0;
	int Policy = 0;
	if(C == 0){
		if(Op == 'A'){
			size = getAPolicyNumberObj.C1.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C1[P];
			getAPolicyNumberObj.C1A.push_back(Policy);
			swap(getAPolicyNumberObj.C1[P],getAPolicyNumberObj.C1.back());
			getAPolicyNumberObj.C1.pop_back();
		}
		else if(Op == 'D'){
			size = getAPolicyNumberObj.C1A.size()-1;
			if(size != 0){
				Policy = getAPolicyNumberObj.C1A.back();
				getAPolicyNumberObj.C1A.pop_back();
			}
		}
		else if(Op == 'P'){
			size = getAPolicyNumberObj.C1.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C1[P];
			swap(getAPolicyNumberObj.C1[P],getAPolicyNumberObj.C1.back());
			getAPolicyNumberObj.C1.pop_back();
		}
		
	}
	if(C == 1){
		if(Op == 'A'){
			size = getAPolicyNumberObj.C2.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C2[P];
			getAPolicyNumberObj.C2A.push_back(Policy);
			swap(getAPolicyNumberObj.C2[P],getAPolicyNumberObj.C2.back());
			getAPolicyNumberObj.C2.pop_back();
		}
		else if(Op == 'D'){
			size = getAPolicyNumberObj.C2A.size()-1;
			if(size != 0){
				Policy = getAPolicyNumberObj.C2A.back();
				getAPolicyNumberObj.C2A.pop_back();
			}
		}
		else if(Op == 'P'){
			size = getAPolicyNumberObj.C2.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C2[P];
			swap(getAPolicyNumberObj.C2[P],getAPolicyNumberObj.C2.back());
			getAPolicyNumberObj.C2.pop_back();
		}
	}
	if(C == 2){
		if(Op == 'A'){
			size = getAPolicyNumberObj.C3.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C3[P];
			getAPolicyNumberObj.C3A.push_back(Policy);
			swap(getAPolicyNumberObj.C3[P],getAPolicyNumberObj.C3.back());
			getAPolicyNumberObj.C3.pop_back();
		}
		else if(Op == 'D'){
			size = getAPolicyNumberObj.C3A.size()-1;
			if(size != 0){
				Policy = getAPolicyNumberObj.C3A.back();
				getAPolicyNumberObj.C3A.pop_back();
			}
		}
		else if(Op == 'P'){
			size = getAPolicyNumberObj.C3.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C3[P];
			swap(getAPolicyNumberObj.C3[P],getAPolicyNumberObj.C3.back());
			getAPolicyNumberObj.C3.pop_back();
		}
	}
	if(C == 3){
		if(Op == 'A'){
			size = getAPolicyNumberObj.C4.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C4[P];
			getAPolicyNumberObj.C4A.push_back(Policy);
			swap(getAPolicyNumberObj.C4[P],getAPolicyNumberObj.C4.back());
			getAPolicyNumberObj.C4.pop_back();
		}
		else if(Op == 'D'){
			size = getAPolicyNumberObj.C4A.size()-1;
			if(size != 0){
				Policy = getAPolicyNumberObj.C4A.back();
				getAPolicyNumberObj.C4A.pop_back();
			}
		}
		else if(Op == 'P'){
			size = getAPolicyNumberObj.C4.size()-1;
			P =  rand() % size + 1;
			Policy = getAPolicyNumberObj.C4[P];
			swap(getAPolicyNumberObj.C4[P],getAPolicyNumberObj.C4.back());
			getAPolicyNumberObj.C4.pop_back();
		}
	}

	retPolicyNumVectors.Pol = Policy;
	retPolicyNumVectors.C1 = getAPolicyNumberObj.C1;
	retPolicyNumVectors.C2 = getAPolicyNumberObj.C2;
	retPolicyNumVectors.C3 = getAPolicyNumberObj.C3;
	retPolicyNumVectors.C4 = getAPolicyNumberObj.C4;

	retPolicyNumVectors.C1A = getAPolicyNumberObj.C1A;
	retPolicyNumVectors.C2A = getAPolicyNumberObj.C2A;
	retPolicyNumVectors.C3A = getAPolicyNumberObj.C3A;
	retPolicyNumVectors.C4A = getAPolicyNumberObj.C4A;

	return retPolicyNumVectors;

}


AddPolicy DecisionPrint(OnePeriod OnePeriodInfo,vector<int> C1, vector<int> C2, vector<int> C3, vector<int> C4, AddPolicy AddList){

	AddPolicy FuncAddList = AddList;

	PolicyNumVectors retPolicyNumVectors;
	retPolicyNumVectors.C1 = C1;
	retPolicyNumVectors.C2 = C2;
	retPolicyNumVectors.C3 = C3;
	retPolicyNumVectors.C4 = C4;
	retPolicyNumVectors.C1A = FuncAddList.C1A;
	retPolicyNumVectors.C2A = FuncAddList.C2A;
	retPolicyNumVectors.C3A = FuncAddList.C3A;
	retPolicyNumVectors.C4A = FuncAddList.C4A;
		
	for(int j=0; j<OnePeriodInfo.OnePeriodList.size(); j++){
		string Ops = OnePeriodInfo.OnePeriodList[j].Op;
		int customer = OnePeriodInfo.OnePeriodList[j].Customer;
		string BW = OnePeriodInfo.OnePeriodList[j].BW;
		int Pstart = 0;
		int size = 0;

		for(int l=0; l< Ops.size(); l++){
			if(Ops[l] != '0'){
				retPolicyNumVectors = getAPolicyNumber(customer, retPolicyNumVectors,Ops[l]);
				PrintInFile(retPolicyNumVectors.Pol,Ops[l],customer,BW);
			}
		}
	}
	PrintInFile(0,'0',0,"0");

	FuncAddList.C1A = retPolicyNumVectors.C1A;
	FuncAddList.C2A = retPolicyNumVectors.C2A;
	FuncAddList.C3A = retPolicyNumVectors.C3A;
	FuncAddList.C4A = retPolicyNumVectors.C4A;

	return FuncAddList;
}

int main (){

	srand((unsigned int) time(0));

	int NoOfPolicies = 0;
	int CustomerID = 0;
	vector<int> PoliciesPerCustomers;

	structPolicyList OriginalPolicyList = gen_PolicyList("Policy.txt", OriginalPolicyList);

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

	int C1Start = 1;
	int C2Start = PoliciesPerCustomers[0] + 1;
	int C3Start = C2Start + PoliciesPerCustomers[1];
	int C4Start = C3Start + PoliciesPerCustomers[2];
	int End = C4Start + PoliciesPerCustomers[3] - 1;

	vector<OnePeriod> ScheduleVec = gen_PeriodicalInfo("Schedule.txt");

	vector<int> C1;
	for(int i=C1Start; i<C2Start; i++){
		C1.push_back(i);
	}

	vector<int> C2;
	for(int i=C2Start; i<C3Start; i++){
		C2.push_back(i);
	}

	vector<int> C3;
	for(int i=C3Start; i<C4Start; i++){
		C3.push_back(i);
	}

	vector<int> C4;
	for(int i=C4Start; i<End; i++){
		C4.push_back(i);
	}

	AddPolicy AddList;

	for(int i=0; i< ScheduleVec.size(); i++){
		AddList = DecisionPrint(ScheduleVec[i], C1, C2, C3, C4, AddList);
	}

return 0;
}