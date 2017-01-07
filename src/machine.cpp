#include "machine.h"

Machine::Machine(int id, int start_t = 0){
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
}

void Machine::set_stop_t(int t){
	stop_t = t;
}

void Machine::add(Task task, vector<Maitenance> maitenance_v){

}


/*
bool Machine::add(int task_id, vector<Task> task_v, vector<Maitenance> maitenance_v){
	if (id == 1){ //machine 1
		Task_t new_task(task_v[task_id]);
		for (vector<Maitenance>::size_type i = 0; i < maitenance_v.size() ; i++ ){
			if (stopt == maitenance_v[i].get_mt()){
				stopt += maitenance_v[i].get_opt();
				new_task.set_op_stime(stopt);
			}
		}

		if (stopt < task_v[task_id].get_rt()){
			return false;
		}

		for(vector<Maitenance>::size_type i = 0; i < maitenance_v.size(); i++){
			if(stopt < maitenance_v[i].get_mt() && (stopt + task_v[task_id].get_op_time(1)) > maitenance_v[i].get_mt()){
				new_task.punishit(task_v[i].get_op_time(1));
				if(task_v[i].get_op_time(1) % 5 == 0){
					new_task.punish();
				}
				new_task.set_op_stime(stopt);
				stopt += maitenance_v[i].get_opt();
			}
		}
		mtasks_v.push_back(new_task);
		stopt += task_v[task_id].get_op_time(1)+new_task.get_punish();
	}else{ // machine 2
		Task_t new_task(task_v[task_id]);
		new_task.set_op_stime(stopt);
		mtasks_v.push_back(new_task);
		stopt += task_v[task_id].get_op_time(2);
	}
	return true;
}

bool Machine::add(Task_t new_task, vector<Maitenance> maitenance_v){
	if (id == 1){ //machine 1
		for (vector<Maitenance>::size_type i = 0; i < maitenance_v.size() ; i++ ){
			if (stopt == maitenance_v[i].get_mt()){
				stopt += maitenance_v[i].get_opt();
				new_task.set_op_stime(stopt);
			}
		}

		if (stopt < new_task.get_rt()){
			return false;
		}

		for(vector<Maitenance>::size_type i = 0; i < maitenance_v.size(); i++){
			if(stopt < maitenance_v[i].get_mt() && (stopt + new_task.get_op_time(1)) > maitenance_v[i].get_mt()){
				new_task.punishit(new_task.get_op_time(1));
				if(new_task.get_op_time(1) % 5 == 0){
					new_task.punish();
				}
				new_task.set_op_stime(stopt);
				stopt += maitenance_v[i].get_opt();
			}
		}
		mtasks_v.push_back(new_task);
		stopt += new_task.get_op_time(1)+new_task.get_punish();
	}else{ // machine 2
		new_task.set_op_stime(stopt);
		mtasks_v.push_back(new_task);
		stopt += new_task.get_op_time(2);
	}
	return true;
}

void Machine::addt(int t, int task_id, vector<Task> task_v){
	if (id == 2){
		Task_t new_task(task_v[task_id]);
		new_task.set_op_stime(stopt);
		mtasks_v.push_back(new_task);
		stopt += t + task_v[task_id].get_op_time(2);
	}
}

void Machine::addt(int t, Task_t new_task){
	if (id == 2){
		new_task.set_op_stime(stopt);
		mtasks_v.push_back(new_task);
		stopt += t + new_task.get_op_time(2);
	}
}
*/
