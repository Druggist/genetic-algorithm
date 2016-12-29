#ifndef MACHINE_H
#define MACHINE_H

#include "task.h"
#include "maitenance.h"
#include <vector>

using std::vector;

class Machine{
	private:
		int id;
		int startt;
		int stopt;
	public:
		vector <Task_t> mtasks_v;
		void set_id(int);
		void set_start(int);
		void set_stop(int);
		bool add(int, vector<Task>, vector<Maitenance>);
		int get_id();
		int get_srt();
		int get_sop();
		void addt(int, int, vector<Task>);
};

#endif // MACHINE_H