#ifndef TASK_H
#define TASK_H

#include <cstdlib>
#include <math.h>

class Task{
	private:
		short id;
		int op1_t, op2_t, ready_t;
		int renewal_t;
		bool punished;
	public:
		Task(short);

		int get_id() const;
		int get_ready_t();
		int get_op_t(int);
		int get_punished_op_t();
		int	get_renewal_t();

		void set_ready_t(int);
		void set_op_t(int, int);
		void punish(int);
		void reset_punishment();

		bool is_punished();
		bool operator== (const Task&);
};

#endif // TASK_H