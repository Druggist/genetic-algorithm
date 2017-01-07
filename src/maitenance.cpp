#include "maitenance.h"

Maitenance::Maitenance(int id){
	this->id = id;
}

int Maitenance::get_id(){
	return id;
}

int Maitenance::get_start_t(){
	return start_t;
}

int Maitenance::get_duration(){
	return duration;
}

void Maitenance::set_start_t(int t){
	this->start_t = t;
}

void Maitenance::set_duration(int d){
	this->duration = d;
}
