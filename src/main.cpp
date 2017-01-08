#include "machine.h"
#include "maitenance.h"
#include "order.h"
#include "task.h"
#include "generations.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>

using std::cout;
using std::string;
using std::fstream;
using std::vector;
using std::endl;

int main(int argc, char* argv[]){
	if (argc != 3){
		cout<<"Usage: "<<argv[0]<<" <inputfile> <outputfile>"<<endl;
		return 1;
	}
	Generations gen(argv[1]);
	gen.next_generation();
	//gen.dump_generation(string(argv[2]));

	//
	//do everything


	return 0;

/*
	vector<Task> task_v;
	vector<Maitenance> maitenance_v;
	string inputFN, outputFN;
	fstream inputF, outputF;
	inputFN = string(argv[1]);
	outputFN = string(argv[2]);
	int e_number;

	inputF.open(inputFN);
	outputF.open(outputFN);

	if( inputF ){
		inputF >> e_number;
		string tmp = "";
		string tmp1, tmp2, tmp3;

		for(int i = 0; i < e_number; i++){
			Task t;
			t.id = i;
			inputF >> tmp;
			tmp = tmp.substr(0, tmp.length() -1);
			t.set_op_time(1, atoi(tmp.c_str()));

			inputF >> tmp >> tmp;
			tmp = tmp.substr(0, tmp.length()-1);
			t.set_op_time(2, atoi(tmp.c_str()));

			inputF >> tmp >>tmp >>tmp;
			tmp = tmp.substr(0, tmp.length()-1);
			t.set_rt(atoi(tmp.c_str()));

			task_v.push_back(t);
		}
		while (inputF >> tmp){
			inputF>>tmp1;
			inputF>>tmp2 >> tmp2;
			inputF>>tmp3 >>tmp3 >>tmp3;
			Maitenance m(atoi(tmp1.substr(0, tmp1.length()-1).c_str()),atoi(tmp2.substr(0, tmp2.length()-1).c_str()),atoi(tmp3.substr(0, tmp3.length()-1).c_str())) ;
			maitenance_v.push_back(m);
		}
		inputF.close();
	}else{
		cout<<"Got some error during opening the file\n";
		return 1;
	}
	
	for(vector<Task>::size_type i = 0; i < task_v.size(); i++){
		cout << task_v[i].get_id() <<";" << task_v[i].get_op_time(1) << ";" << task_v[i].get_op_time(2)<<";"<<task_v[i].get_rt()<<std::endl;
	}
	for(vector<Maitenance>::size_type i = 0; i < maitenance_v.size(); i++){
		cout<<maitenance_v[i].get_id() <<";" << maitenance_v[i].get_mt() << maitenance_v[i].get_opt()<<std::endl; 
	}
	//Scheduling
	cout<<"Scheduling:\n";
	vector <int> s;
	int m = 2000;
	int temp = 0;
	vector <Order> orders;

	for(int i = 0; i < e_number; i++) s.push_back(i);
	for(int i = 0; i < 10; i++){
		Order ord;
		random_shuffle(s.begin(), s.end());
		ord.initialization(s, task_v, maitenance_v);
		orders.push_back(ord);
		if(ord.machine2.get_sop() < m){
			m = ord.machine2.get_sop();
			temp = i;
		}
		cout<< "schedule " << i << std::endl <<"\t" << ord.machine2.get_sop() << std::endl;
	}
	cout << temp << " " << m << std::endl;
	return 0;*/
}
