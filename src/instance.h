#ifndef INSTANCE_H
#define INSTANCE_H

#include "task.h"
#include "maitenance.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cerr;
using std::vector;
using std::endl;
using std::fstream;
using std::string;

class Instance{
	int id, tasks_number;
	vector<Task> task_v;
	vector<Maitenance> maitenance_v;
public:
	void generate_instance(int, int, bool);
	void dump_instance(string);
	void read_instance(string);
	void clear_task_v();
	void clear_maitenance_v();
};

#endif // INSTANCE_H

