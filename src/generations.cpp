#include "generations.h"

Generations::Generations(vector<Maitenance> maintanance_v){
	this->population_id = 0;
	this->maintanance_v = maintanance_v;
	
}

void Generations::selection(){

}

void Generations::rebuild(vector<Task_t>& tasks_m1, vector<Task_t>& tasks_m2, int resection_m1, int resection_m2){
/*or (int i = 0; i < resection; i++){
		for (int j = resection; j < tasks.size(); j++){
			if (tasks[i].get_id() == tasks[j].get_id()){
				population.erase(population.begin() + j);
				break;
			}
		}
	}*/
		// TODO REMOVE DUPLICATES & ADD MISSING
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

void Generations::fix(vector<Task_t>& tasks_m1, std::vector<Task_t>& tasks_m2){
	// TODO RESIZE & READYTIME
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
	int resection_m1 = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection_m1 <= 0) return false;
	
	vector<Task_t> tasks_m1(&tmp[0], &tmp[resection_m1 - 1]);
	vector<Task_t> tasks_m1_2(&tmp[resection_m1], &tmp[tmp.size() - 1]);
	tasks_m1.insert(tasks_m1.end(), tasks_m1_2.begin(), tasks_m1_2.end());
	

	tmp = previous_population[instance1_num].order->get_tasks(2);
	int resection_m2 = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection_m2 <= 0) return false;
	
	vector<Task_t> tasks_m2(&tmp[0], &tmp[resection_m2 - 1]);
	vector<Task_t> tasks_m2_2(&tmp[resection_m2], &tmp[tmp.size() - 1]);
	tasks_m2.insert(tasks_m2.end(), tasks_m2_2.begin(), tasks_m2_2.end());

	this->rebuild(tasks_m1, tasks_m2, resection_m1, resection_m2);
	this->fix(tasks_m1, tasks_m2);

	Instance *new_instance = new Instance;
	new_instance->order = new Order(tasks_m1, tasks_m2, this->maintanance_v);
	new_instance->rank = 0;
	population[instance_id] = *new_instance;

	return true;
}

void Generations::mutate(int instance_id){
	random_device rd;
	mt19937_64 gen(rd());
	vector<Task_t> tasks_m1 = population[instance_id].order->get_tasks(1);
	uniform_int_distribution<int> random_task_m1(0, tasks_m1.size() - 1);
	vector<Task_t> tasks_m2 = population[instance_id].order->get_tasks(2);
	uniform_int_distribution<int> random_task_m2(0, tasks_m2.size() - 1);
	int task_m1[2], task_m2[2];

	task_m1[0] = random_task_m1(gen);
	while(task_m1[0] == task_m1[1]) task_m1[1] = random_task_m1(gen);
	task_m2[0] = random_task_m2(gen);
	while(task_m2[0] == task_m2[1]) task_m2[1] = random_task_m2(gen);

	iter_swap(tasks_m1.begin() + task_m1[0], tasks_m1.begin() + task_m1[1]);
	iter_swap(tasks_m2.begin() + task_m2[0], tasks_m2.begin() + task_m2[1]);

	this->fix(tasks_m1, tasks_m2);

	Instance *new_instance = new Instance;
	new_instance->order = new Order(tasks_m1, tasks_m2, this->maintanance_v);
	new_instance->rank = 0;
	population[instance_id] = *new_instance;
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
		if(random_mutation(gen) < _MUTATION_CHANCE_PCT) mutate(i);
	}
	this->population_id++;
}