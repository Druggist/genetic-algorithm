#include "maitenance.h"

Maitenance::Maitenance(int i, int m_t, int stime){
	m_time = m_t;
	op_time = stime;
	id = i;
}

int Maitenance::get_mt(){
	return m_time;
}

int Maitenance::get_id(){
	return id;
}

int Maitenance::get_opt(){
	return op_time;
}