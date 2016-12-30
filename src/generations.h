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
	Order order;
	double rank;
};

struct Less_than_rank{
	inline bool operator() (const Instance&, const Instance&);
};

class Generations{
	private: 
		vector<Instance> previous_population;
		vector<Instance> population;
	public:
		Generations();
		void selection();
		void rebuild();
		void remove_weak();
		void crossing_over();
		void mutate();
		void sort_population();
};
#endif // GENERATIONS_H