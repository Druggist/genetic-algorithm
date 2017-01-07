#include "machine.h"
#include <iostream>
void Machine::set_id(int i){
	id = i;
}

void Machine::set_start(int i){
	startt = i;
}

void Machine::set_stop(int i){
	stopt = i;
}

int Machine::get_id(){
	return id;
}

int Machine::get_srt(){
	return startt;
}

int Machine::get_sop(){
	return stopt;
}

bool Machine::add(int task_id, vector<Task> task_v, vector<Maitenance> maitenance_v){
	 std::cout<<"machine::add/n";
	if (id == 1){ //machine 1
        std::cout<<"machine1::add::/n";
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
