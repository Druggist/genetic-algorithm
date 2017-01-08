#include "machine.h"

void Machine::init(short id, int start_t = 0){
	this->id = id;
	this->start_t = start_t;
	this->stop_t = start_t;
}

int Machine::get_id(){
	return id;
}

int Machine::get_start_t(){
	return start_t;
}

int Machine::get_stop_t(){
	return stop_t;
}

vector<Task> Machine::get_tasks(){
	return tasks;
}

void Machine::set_start_t(int t){
	start_t = t;
	stop_t = t;
}

void Machine::set_stop_t(int t){
	stop_t = t;
}

bool Machine::add(Task task, vector<Maitenance> maitenance_v){
	if (id == 1){
		int overlay = 0;
		int maitenance_id = 0;

		for (unsigned int i = 0; i < maitenance_v.size(); i++){
			if(maitenance_v[i].get_start_t() < stop_t || maitenance_v[i].get_stop_t() > stop_t) this->stop_t = maitenance_v[i].get_stop_t();
			if(maitenance_v[i].get_start_t() > stop_t){
				int task_t = (overlay == 0)?(task.get_op_t(1)):(task.get_punished_op_t());
				if(maitenance_v[i].get_start_t() <= task_t){
					overlay++;
					maitenance_id = i;
				}else if(overlay <= 1) break;
				if(overlay > 1) return false;
			}
		}

		if(overlay == 0) this->stop_t += task.get_op_t(1);
		else{
			this->stop_t += maitenance_v[maitenance_id].get_duration() + task.get_punished_op_t();
			task.punish(maitenance_v[maitenance_id].get_stop_t());
		}
		tasks.push_back(task);
	}else if( id == 2){
		tasks.push_back(task);
		this->stop_t += task.get_op_t(2);
	}
	return true;
}
