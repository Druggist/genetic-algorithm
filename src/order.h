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
		int exec_t;
	public:
		Order(vector<Task> tasks);
		
		int get_exectime();
		vector<Task> get_tasks();
		
		//  Order();
		//	Order(vector<Task_t>, vector<Task_t>, vector<Maitenance>);
		//void initialization(vector<int>, vector<Task>, vector<Maitenance>);
};

#endif // ORDER_H
