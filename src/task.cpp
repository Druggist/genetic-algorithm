#include "task.h"

int Task::get_id(){
	return id;
}

int Task::get_rt(){
	return rt;
}

int Task::get_op_time(int i){
	if (i == 1)	return op1_time;
	if (i == 2)	return op2_time;
	return -1;
}

void Task::set_rt(int i){
	rt = i;
}

void Task::set_op_time(int o, int t){
	if (o == 1) op1_time = t;
	else if (o == 2) op2_time = t;
	else exit(1);
}

Task_t::Task_t(int i){
	punished = false;
	punishment = 0;
	id = i;
}

int Task_t::get_id(){
	return id;
}

bool Task_t::if_punished(){
	return punished;
}

int Task_t::get_punish(){
	return punishment;
}

int Task_t::punish_time(){
	return punishment;
}

void Task_t::punishit(int p){
	punished = true;
	punishment = p;
}

void Task_t::punish(){
	punishment++;
}

int Task_t::get_rt(){
	return rt;
}

int Task_t::startt(){
	return op_stime;
}

void Task_t::set_op_stime(int k){
	op_stime = k;
}