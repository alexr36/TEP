#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"
#include "CGeneticAlgorithm.h"

#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

namespace NGroupingChallenge
{
	class COptimizer
	{
	public:
		COptimizer(CGroupingEvaluator& cEvaluator);
		~COptimizer();

		void vInitialize();
		void vRunIteration();
		void initializeAlgorithm();
		void runAlgorithm(int maxIterations);

		vector<int>* pvGetCurrentBest() { return &v_current_best; }
		double getCurrentBestFitness() { return d_current_best_fitness; }

	private:
		CGroupingEvaluator& c_evaluator; 

		double d_current_best_fitness;
		vector<int> v_current_best;

		mt19937 c_random_engine;

		CGeneticAlgorithm* genetic_algorithm = nullptr;
		int iter = 0;
	};
}

#endif