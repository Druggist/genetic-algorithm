#include "task.h"

Task::Task(int id){
	this->id  = id;
	reset_punishment();
}

int Task::get_id() const{
	return id;
}

int Task::get_ready_t(){
	return ready_t;
}

int Task::get_op_t(int i){
	if (i == 1)	return op1_t;
	return op2_t;
}

int Task::get_punished_op_t(){
	return ceil(1.2 * op1_t);
}

int Task::get_renewal_t(){
	return renewal_t;
}

void Task::set_ready_t(int t){
	this->ready_t = t;
}

void Task::set_op_t(int o, int t){
	if (o == 1) op1_t = t;
	else if (o == 2) op2_t = t;
}

void Task::punish(int t){
	this->renewal_t = t;
	this->punished = true;
}

void Task::reset_punishment(){
	this->renewal_t = 0;
	punished = false;
}

bool Task::if_punished(){
	return punished;
}

bool Task::operator==(const Task& r){
	if(this->get_id() == r.get_id()) return true;
	return false;
}