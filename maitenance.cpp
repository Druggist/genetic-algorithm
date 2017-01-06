#include "maitenance.h"


int Maitenance::get_mt(){
	return m_time;
}

int Maitenance::get_id(){
	return id;
}

int Maitenance::get_opt(){
	return op_time;
}

void Maitenance::set_id(int i){
  id = i;
}

void Maitenance::set_mt(int m){
  m_time = m;
}

void Maitenance::set_opt(int o){
  op_time = o;
}
