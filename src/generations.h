#ifndef GENERATIONS_H
#define GENERATIONS_H

#include "order.h"
#include "config.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>

using std::vector;
using std::sort;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;

struct Instance{
	Order *order;
	double rank;
};

struct Less_than_rank{
	inline bool operator() (const Instance&, const Instance&);
};

class Generations{
	private: 
		unsigned int population_id;
		vector<Instance> previous_population;
		vector<Instance> population;
		vector<Maitenance> maintanance_v;
		void fix(vector<Task_t>&, vector<Task_t>&);
		void rebuild(vector<Task_t>&, vector<Task_t>&, int, int);
		bool crossing_over(int);
		void remove_weak();
		void selection();
		void mutate();
		void sort_population();
	public:
		void next_generation();
		Generations(vector<Maitenance>);
};
#endif // GENERATIONS_H