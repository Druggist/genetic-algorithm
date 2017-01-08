#include "order.h"

void Order::init(vector<Task> tasks, vector<Maitenance> maitenance_v){
	int machine1_ready_time = 10000, first_job_rt_pos = 0, iter;
	if (tasks[0].get_ready_t() == 0) {machine1_ready_time = 0;}
	else{
		   //finding smallest ready_time
			for (unsigned int i = 0; i < tasks.size(); i++){
				if (tasks[i].get_ready_t() < machine1_ready_time) {
				machine1_ready_time = tasks[i].get_ready_t();
				first_job_rt_pos = i;
			}
	  }
	//swapping jobs with first
		iter_swap(tasks.begin()+0, tasks.begin()+first_job_rt_pos);
	}
	machine1.init(1, tasks[0].get_ready_t());
	machine2.init(2, tasks[0].get_ready_t());
	for (unsigned int i = 0; i < tasks.size(); i++){
		iter = i;
		if (machine1.get_stop_t() >= tasks[i].get_ready_t()){ // when  fits perfectly

			while (!machine1.add(tasks[i], maitenance_v)){
				tasks.push_back(tasks[i]);
				tasks.erase(tasks.begin()+i);
                iter++;
                if (iter == tasks.size())
                {
                    iter = i;
                    break;
                }
			}
            if( machine2.get_stop_t() >= machine1.get_stop_t()){
                machine2.add(tasks[i], maitenance_v);
		}else{
			machine2.set_stop_t(machine1.get_stop_t());
			machine2.add(tasks[i], maitenance_v);}

		}
		else{ // if machine1.get_stop_t() > tasks[i].get_ready_t()
			for (unsigned int j = i + 1; j < tasks.size(); j++){
				if(machine1.get_stop_t() >= tasks[i].get_ready_t()){
					iter_swap(tasks.begin()+i, tasks.begin()+j);
					break;
				}
				if ( j == tasks.size() -1 ){
                    machine1.set_stop_t(tasks[i].get_ready_t());
				}
			}
			i--;
		}

	}
}

int Order::get_exectime(){
	return exec_t;
}

vector<Task> Order::get_tasks(){
	return this->machine1.get_tasks();
}
