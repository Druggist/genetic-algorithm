#include "generations.h"
//TODO: time-based killing
Generations::Generations(string filename){
	this->population_id = 0;
	this->begin_exec = clock();
	Instance I;
	vector <int> s;
	vector <Order> orders;
	int m = 2000;
	int tmp = 0;
    Chromosome zero;
	I.read_instance(filename);
	for(vector<Task_t>::size_type i = 0; i> I.task_v.size(); i++) s.push_back(i);
	for(unsigned int i = 0; i < _POPULATION_SIZE; i++){
	    Order ord; //todo constructor
		random_shuffle(s.begin(), s.end());
		ord.initialization(s, I.task_v, I.maitenance_v);
		orders.push_back(ord);
		if(ord.machine2.get_sop() < m){
			m = ord.machine2.get_sop();
			tmp = i;
		}
      zero.order = &ord;
      zero.rank = 0;
      this->population.push_back(zero);
      this->previous_population.push_back(zero);
	}
    this->maintanance_v = I.maitenance_v;
	
}
int Generations::average(){
  int av = 0;
  for (vector<Chromosome>::size_type i = 0; i < population.size(); i++ ){
    av += previous_population[i].order->get_exectime();
  }
  return av / _POPULATION_SIZE;
}

void Generations::selection(){
  unsigned int av;
  double r;
  unsigned int counter = 0;
  if (population_id == 0){
    av = 0;
  }
  else{
    av = average();
  }

  for (vector<Chromosome>::size_type i = 0; i < population.size(); i++ ){
    r = ((population[i].order->get_exectime() * 100) / av) * _IMPROVE_WEIGHT  + population[i].order->get_exectime() * _EXEC_TIME_WEIGHT;
    if (population[i].order->get_exectime() >= 0.80 * av){
      counter++;
    }
    population[i].rank = r;
  }
  if (counter >= 0.30 * av){
    remove_weak();
  }
  else{
   // TODO: operate again on previous_population
   this->population = this->previous_population;
   next_generation();

  }
}

void Generations::rebuild(vector<Task_t>& tasks_m1, vector<Task_t>& tasks_m2, int resection_m1, int resection_m2){
	for (int x = 1; x < 3; x++){
		vector<int> missing_tasks;
		vector<int> duplicates;
		vector<Task_t> all_tasks = previous_population[0].order->get_tasks(x); //wtf
		int resection = (x == 1)?(resection_m1):(resection_m2);
		vector<Task_t> tasks = (x == 1)?(tasks_m1):(tasks_m2);

		for (int i = 0; i < resection; i++){
			if(find(tasks.begin(), tasks.end(), all_tasks[i]) != tasks.end()) missing_tasks.push_back(i);
			for (unsigned int j = resection; j < tasks.size(); j++){
				if (tasks[i] == tasks[j]){
					duplicates.push_back(j);
					break;
				}
			}
		}
		
		for (unsigned int i = resection; i < tasks.size(); i++){
			if(find(tasks.begin(), tasks.end(), all_tasks[i]) != tasks.end()) missing_tasks.push_back(i); 
		}

		for (unsigned int i = 0; i < duplicates.size(); i++){
			tasks[duplicates[i]] = all_tasks[i];
		}

		if (x == 1) tasks_m1 = tasks;
		else tasks_m2 = tasks;

		time_exceeded();
	}
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
	time_exceeded();
	this->previous_population = this->population;
}

bool Generations::crossing_over(int chromosome_id){
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> random_resection(_MIN_RESECTION_PCT, _MAX_RESECTION_PCT);
	uniform_int_distribution<int> random_chromosome(0, floor(_POPULATION_SIZE * _REMOVE_PCT/100.0) - 1);
	
	int chromosome1_num = random_chromosome(gen);
	int chromosome2_num = random_chromosome(gen);
	while(chromosome1_num == chromosome2_num) chromosome2_num = random_chromosome(gen);
	vector<Task_t> tmp = previous_population[chromosome1_num].order->get_tasks(1);
	int resection_m1 = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection_m1 <= 0) return false;
	
	vector<Task_t> tasks_m1(&tmp[0], &tmp[resection_m1 - 1]);
	vector<Task_t> tasks_m1_2(&tmp[resection_m1], &tmp[tmp.size() - 1]);
	tasks_m1.insert(tasks_m1.end(), tasks_m1_2.begin(), tasks_m1_2.end());
	

	tmp = previous_population[chromosome1_num].order->get_tasks(2);
	int resection_m2 = floor(tmp.size() * random_resection(gen)/100.0);
	if (resection_m2 <= 0) return false;
	
	vector<Task_t> tasks_m2(&tmp[0], &tmp[resection_m2 - 1]);
	vector<Task_t> tasks_m2_2(&tmp[resection_m2], &tmp[tmp.size() - 1]);
	tasks_m2.insert(tasks_m2.end(), tasks_m2_2.begin(), tasks_m2_2.end());

	this->rebuild(tasks_m1, tasks_m2, resection_m1, resection_m2);

	Chromosome *new_chromosome = new Chromosome;
	new_chromosome->order = new Order(tasks_m1, tasks_m2, this->maintanance_v);
	new_chromosome->rank = 0;
	population[chromosome_id] = *new_chromosome;
	time_exceeded();

	return true;
}

void Generations::mutate(int chromosome_id){
	random_device rd;
	mt19937_64 gen(rd());
	vector<Task_t> tasks_m1 = population[chromosome_id].order->get_tasks(1);
	uniform_int_distribution<int> random_task_m1(0, tasks_m1.size() - 1);
	vector<Task_t> tasks_m2 = population[chromosome_id].order->get_tasks(2);
	uniform_int_distribution<int> random_task_m2(0, tasks_m2.size() - 1);
	int task_m1[2], task_m2[2];

	task_m1[0] = random_task_m1(gen);
	while(task_m1[0] == task_m1[1]) task_m1[1] = random_task_m1(gen);
	task_m2[0] = random_task_m2(gen);
	while(task_m2[0] == task_m2[1]) task_m2[1] = random_task_m2(gen);

	iter_swap(tasks_m1.begin() + task_m1[0], tasks_m1.begin() + task_m1[1]);
	iter_swap(tasks_m2.begin() + task_m2[0], tasks_m2.begin() + task_m2[1]);

	Chromosome *new_chromosome = new Chromosome;
	new_chromosome->order = new Order(tasks_m1, tasks_m2, this->maintanance_v);
	new_chromosome->rank = 0;
	population[chromosome_id] = *new_chromosome;
	time_exceeded();
}

inline bool Less_than_rank::operator() (const Chromosome& chromosome1, const Chromosome& chromosome2){
	return (chromosome1.rank < chromosome2.rank);
}

void Generations::sort_population(){
	sort(population.begin(), population.end(), Less_than_rank());
	time_exceeded();
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
	time_exceeded();
}

void Generations::dump_generation(string filename){
  ofstream dump;
  dump.open(filename.c_str());
  dump << "***" /*<< id*/ << "****" << endl;
  dump << population[0].order->get_exectime() /*<< gen_exec_time*/ << endl;
  dump << "M1:";
  vector <Task_t> t;
  t = population[0].order->get_tasks(1);
  for(int i = 0; i < t.size(); i++){
  	dump << t[i] << ',';
  }
  dump << endl;
  t = population[0].order->get_tasks(2);
  for(int i = 0; i < t.size(); i++){
  	dump << t[i] << ',';
  }
  dump << endl;
  //dump << this->maitenance_v.size() << endl << '0' << endl;
  dump.close();
  
}
bool Generations::time_exceeded(){
	clock_t end = clock();
	double elapsed_secs = double(end - this->begin_exec);
	if(elapsed_secs > _EXEC_TIME_SECS) {
		save_and_exit();
		return true;
	}
	return false;
}

void Generations::save_and_exit(string filename){
	dump_generation(filename);
	exit(0);
}
