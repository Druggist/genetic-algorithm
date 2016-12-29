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
		Machine machine1;
		Machine machine2;
		void initialization(vector<int>, vector<Task>, vector<Maitenance>);
};

#endif // ORDER_H