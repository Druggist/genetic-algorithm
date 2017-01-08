#ifndef MACHINE_H
#define MACHINE_H

#include "task.h"
#include "maitenance.h"
#include <vector>

using std::vector;

class Machine{
	private:
		short id;
		int start_t;
		int stop_t;
		vector<Task> tasks;
	public:
		void init(short, int);
		int get_id();
		int get_start_t();
		int get_stop_t();
		vector<Task> get_tasks();

		void set_start_t(int);
		void set_stop_t(int);

		int add(Task, vector<Maitenance>);
};

#endif // MACHINE_H
