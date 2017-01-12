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
	int iter = 1;
	string path;
	for(int j= 0; j < 22;j++) path += argv[2][j];
	for(int i = 0; i < atoi(argv[3]); i++) {
		clock_t end = clock();
		double elapsed_secs = double(end - gen.get_begin_exec()) / CLOCKS_PER_SEC;

		while(iter <= floor(elapsed_secs)){
			if(iter < 10) gen.dump_generation(path+"0"+std::to_string(iter)+".txt");
			else gen.dump_generation(path + std::to_string(iter)+".txt");
			iter++;
		}
		gen.next_generation();
	}
	gen.dump_generation(path+"60.txt");
	return 0;
}
