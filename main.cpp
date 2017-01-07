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
	Generations gen("file.txt");
	cout<<"done"<<endl;
	gen.next_generation();
	cout<<"dupa"<<endl;
	gen.dump_generation(string(argv[2]));

	//
	//do everything


	return 0;
}
