#include "generations.h"

Generations::Generations(){
	
}

void Generations::selection(){

}

void Generations::rebuild(){

}

void Generations::remove_weak(){
	int to_remove = floor(_POPULATION_SIZE*_REMOVE_PCT);
	random_device rd;
  	mt19937_64 gen(rd());
  	uniform_int_distribution<int> dist(0, 99);

  	for(int i = _POPULATION_SIZE - 1; i >= 0; i--){
  		if(dist(gen) >= _REMOVE_FAIL_PCT){
  			population.erase(population.begin() + i);
			to_remove--;
		}
  		if (to_remove == 0) break;
  	}
}

void Generations::crossing_over(){

}

void Generations::mutate(){

}

inline bool Less_than_rank::operator() (const Instance& instance1, const Instance& instance2){
	return (instance1.rank < instance2.rank);
}

void Generations::sort_population(){
	sort(population.begin(), population.end(), Less_than_rank());
}