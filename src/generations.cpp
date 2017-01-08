#include "generations.h"
//TODO: time-based killing
Generations::Generations(string filename){
	this->population_id = 0;
	this->begin_exec = clock();

	Instance instance;
	Chromosome chromosome;
	
	instance.read_instance(filename);
	for(unsigned int i = 0; i < _POPULATION_SIZE; i++){
		vector<Task> tasks(instance.get_tasks());
		random_shuffle(tasks.begin(), tasks.end());

		Order order; 
		order.init(tasks, instance.get_maitenances()); 
		chromosome.order = order;
		chromosome.rank = 0;
		this->population.push_back(chromosome);
	}

	this->previous_population = population;
	this->maintanance_v = instance.get_maitenances();
}

int Generations::average(){
	int av = 0;
	for (vector<Chromosome>::size_type i = 0; i < population.size(); i++ ){
		av += previous_population[i].order.get_exectime();
	}
	return av / _POPULATION_SIZE;
}

void Generations::selection(){
	unsigned int av;
	double r;
	unsigned int counter = 0;
	if (population_id == 0) av = 0;
	else av = average();

	for (vector<Chromosome>::size_type i = 0; i < population.size(); i++ ){
		r = ((population[i].order.get_exectime() * 100) / av) * _IMPROVE_WEIGHT  + population[i].order.get_exectime() * _EXEC_TIME_WEIGHT;
		if (population[i].order.get_exectime() >= 0.80 * av) counter++;
		population[i].rank = r;
	}
	if (counter >= 0.30 * av) remove_weak();
	else{
		// TODO: operate again on previous_population
		this->population = this->previous_population;

		next_generation();
	}
}

void Generations::rebuild(vector<Task>& tasks, int resection){
		vector<int> missing_tasks;
		vector<int> duplicates;
		vector<Task> all_tasks = previous_population[0].order.get_tasks();

		for (int i = 0; i < resection; i++){
			if(find(tasks.begin(), tasks.end(), all_tasks[i]) != tasks.end()) missing_tasks.push_back(i);
			for (unsigned int j = resection; j < tasks.size(); j++){
				if (tasks[i] == tasks[j]){
					duplicates.push_back(j);
					break;
				}
			}
		}
		
		for (unsigned int i = resection; i < all_tasks.size(); i++){
			if(find(tasks.begin(), tasks.end(), all_tasks[i]) != tasks.end()) missing_tasks.push_back(i); 
		}
		for (unsigned int i = 0; i < duplicates.size(); i++) tasks[duplicates[i]] = all_tasks[i];

		time_exceeded();
}

void Generations::remove_weak(){
	int remove_count = floor(_POPULATION_SIZE * _REMOVE_PCT/100.0);
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dist(0, 99);
	vector<int> to_remove;

	sort_population();
	for(int i = _POPULATION_SIZE - 1; i >= 0; i--){
		if(dist(gen) >= _REMOVE_FAIL_PCT){
			population.erase(population.begin() + i);
			remove_count--;
		}
		if (remove_count == 0) break;
	}

	time_exceeded();

	this->previous_population = this->population;
}

bool Generations::crossing_over(int itterator){
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> random_resection(_MIN_RESECTION_PCT, _MAX_RESECTION_PCT);
	uniform_int_distribution<int> random_chromosome(0, floor(_POPULATION_SIZE * _REMOVE_PCT/100.0) - 1);
	int chromosome1_num = random_chromosome(gen);
	int chromosome2_num = random_chromosome(gen);
	while(chromosome1_num == chromosome2_num) chromosome2_num = random_chromosome(gen);
	vector<Task> tmp(previous_population[chromosome1_num].order.get_tasks());
	int resection = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection <= 0) return false;
	vector<Task> tasks(&tmp[0], &tmp[resection - 1]);
	tmp = previous_population[chromosome2_num].order.get_tasks();
	vector<Task> tasks2(&tmp[resection], &tmp[tmp.size() - 1]);
	tasks.insert(tasks.end(), tasks2.begin(), tasks2.end());

	this->rebuild(tasks, resection);

	Order order;
	order.init(tasks, this->maintanance_v);
	Chromosome new_chromosome;
	new_chromosome.order = order;
	new_chromosome.rank = 0;
	this->population.push_back(new_chromosome);

	time_exceeded();

	return true;
}

void Generations::mutate(int chromosome_id){
	random_device rd;
	mt19937_64 gen(rd());
	vector<Task> tasks = population[chromosome_id].order.get_tasks();
	uniform_int_distribution<int> random_task_id(0, tasks.size() - 1);
	int task_id[2];

	task_id[0] = random_task_id(gen);
	while(task_id[0] == task_id[1]) task_id[1] = random_task_id(gen);

	iter_swap(tasks.begin() + task_id[0], tasks.begin() + task_id[1]);

	Order order;
	order.init(tasks, this->maintanance_v);
	Chromosome new_chromosome;
	new_chromosome.order = order;
	new_chromosome.rank = 0;
	population[chromosome_id] = new_chromosome;

	time_exceeded();
}

inline bool Less_than_rank::operator() (const Chromosome& chromosome1, const Chromosome& chromosome2){
	return (chromosome1.rank < chromosome2.rank);
}

void Generations::sort_population(){
	sort(population.begin(), population.end(), Less_than_rank());
}

void Generations::next_generation(){
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> random_mutation(0, 100);

	remove_weak();

	this->population.clear();
	for (unsigned int i = 0; i < _POPULATION_SIZE; i++){
		crossing_over(i);
		if(random_mutation(gen) < _MUTATION_CHANCE_PCT) {
			mutate(i);
		}
	}
	this->population_id++;

	time_exceeded();
}

void Generations::dump_generation(string filename){
	ofstream dump;
	dump.open(filename.c_str());
	dump << "***" /*<< id*/ << "****" << endl;
	//rank
	sort_population();
	dump << population[0].order.get_exectime() /*<< gen_exec_time*/ << endl;
	dump << "M1:";
	vector <Task> t = population[0].order.get_tasks();
	// for(int i = 0; i < t.size(); i++) dump << t[i] << ',';
	dump << endl;
//	t = population[0].order->get_tasks(2);
	//for(int i = 0; i < t.size(); i++){
//	dump << t[i] << ',';
//	}
	dump << endl;
	//dump << this->maitenance_v.size() << endl << '0' << endl;
	dump.close();
	
}
bool Generations::time_exceeded(){
	clock_t end = clock();
	double elapsed_secs = double(end - this->begin_exec);
	if(elapsed_secs > _EXEC_TIME_SECS){
	//	save_and_exit("data/out.txt");
		return true;
	}
	return false;
}

void Generations::save_and_exit(string filename){
	dump_generation(filename);
	exit(0);
}
