#include "generations.h"

Generations::Generations(vector<Maitenance> maintanance_v){
	this->population_id = 0;
	this->maintanance_v = maintanance_v;
	
}

void Generations::selection(){

}

void Generations::rebuild(vector<Task_t>& tasks_m1, vector<Task_t>& tasks_m2){

}

void Generations::remove_weak(){
	int to_remove = floor(_POPULATION_SIZE * _REMOVE_PCT/100.0);
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dist(0, 99);

	sort_population();
	for(int i = _POPULATION_SIZE - 1; i >= 0; i--){
		if(dist(gen) >= _REMOVE_FAIL_PCT){
			population.erase(population.begin() + i);
			to_remove--;
		}
		if (to_remove == 0) break;
	}
	this->previous_population = this->population;
}

void Generations::remove_duplicates(vector<Task_t>& tasks, int resection){
	for (int i = 0; i < resection; i++){
		for (int j = resection; j < tasks.size(); j++){
			if (tasks[i].get_id() == tasks[j].get_id()){
				population.erase(population.begin() + j);
				break;
			}
		}
	}
}

bool Generations::crossing_over(int instance_id){
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> random_resection(_MIN_RESECTION_PCT, _MAX_RESECTION_PCT);
	uniform_int_distribution<int> random_instance(0, floor(_POPULATION_SIZE * _REMOVE_PCT/100.0) - 1);
	
	int instance1_num = random_instance(gen);
	int instance2_num = random_instance(gen);
	while(instance1_num == instance2_num) instance2_num = random_instance(gen);
	vector<Task_t> tmp = previous_population[instance1_num].order->get_tasks(1);
	int resection = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection <= 0) return false;
	vector<Task_t> tasks_m1(&tmp[0], &tmp[resection - 1]);
	

	tmp = previous_population[instance1_num].order->get_tasks(2);
	vector<Task_t> tasks_m2(&tmp[resection], &tmp[tmp.size() - 1]);
	resection = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection <= 0) return false;

	this->remove_duplicates(tasks_m1, resection);
	this->remove_duplicates(tasks_m2, resection);
	this->rebuild(tasks_m1, tasks_m2);

	Instance *new_instance = new Instance;
	new_instance->order = new Order(tasks_m1, tasks_m2, this->maintanance_v);
	new_instance->rank = 0;
	population[instance_id] = *new_instance;

	return true;
}

void Generations::mutate(){

//	this->rebuild(tasks_m1, tasks_m2);
}

inline bool Less_than_rank::operator() (const Instance& instance1, const Instance& instance2){
	return (instance1.rank < instance2.rank);
}

void Generations::sort_population(){
	sort(population.begin(), population.end(), Less_than_rank());
}

void Generations::next_generation(){
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> random_mutation(0, 100);

	remove_weak();
	for (unsigned int i = 0; i < _POPULATION_SIZE; i++){
		crossing_over(i);
		if(random_mutation(gen) < _MUTATION_CHANCE_PCT) mutate();
	}
	this->population_id++;
}