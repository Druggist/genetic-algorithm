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
	if (argc != 4){
		cout<<"Usage: "<<argv[0]<<" <inputfile> <outputfile> <generations count>"<<endl;
		return 1;
	}
	Generations gen(argv[1], argv[2]);
		for(int i = 0; i < atoi(argv[3]); i++) {
		gen.next_generation();
		if(i == 50 || i == 150){
		string s;
		for(int j= 0; j < 21;j++) s += argv[2][j];
		s += "_"+std::to_string(i)+".txt";
		gen.dump_generation(s);
		}
		if(i % 100 == 0) {
		string s;
		for(int j= 0; j < 21;j++) s += argv[2][j];
		s += "_"+std::to_string(i)+".txt";
		gen.dump_generation(s);
		}
	}
		string s;
		for(int j= 0; j < 21;j++) s += argv[2][j];
		s += "_15000.txt";
	gen.dump_generation(s);
	return 0;
}
