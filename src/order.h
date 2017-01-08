#ifndef ORDER_H
#define ORDER_H

#include "machine.h"
#include "task.h"
#include "maitenance.h"
#include <vector>

using std::vector;

class Order{
	private:
		Machine machine1, machine2;
	public:
		void init(vector<Task>, vector<Maitenance>);
        int get_machine_start_t(int);
		int get_exectime();
		vector<Task> get_tasks();
		vector<Task> get_tasks_2();
};

#endif // ORDER_H
