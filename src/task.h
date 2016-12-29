#ifndef TASK_H
#define TASK_H

#include <cstdlib>

struct Task{
	int id;
	int op1_time;
	int op2_time;
	int rt;
	int get_id();
	int get_rt();
	int get_op_time(int);
	void set_op_time(int, int);
	void set_rt(int);
};

class Task_t : private Task{
	private:
		bool punished;
		int punishment; //summary punishment time
		int op_stime; //start time
	public:
		Task_t(int);
		bool if_punished();
		int punish_time();
		void punishit(int);
		void punish();
		int startt();
		int get_id();
		int get_rt();
		int get_punish();
		void set_op_stime(int);
};

#endif // TASK_H