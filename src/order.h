#ifndef ORDER_H
#define ORDER_H

#include "machine.h"
#include "task.h"
#include "maitenance.h"
#include <vector>

using std::vector;

class Order{
	private:
		vector<int> ord;
		int exec_t;
	public:
        Order();
		Order(vector<Task_t>, vector<Task_t>, vector<Maitenance>);
		Machine machine1;
		Machine machine2;
		void initialization(vector<int>, vector<Task>, vector<Maitenance>);
		vector<Task_t> get_tasks(int);
        int get_exectime();
};

#endif // ORDER_H
