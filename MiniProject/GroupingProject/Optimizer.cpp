#include "Optimizer.h"
#include "CGeneticAlgorithm.h"
#include "Constants.h"

using namespace NGroupingChallenge;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_random_engine.seed(c_seed_generator());
}

COptimizer::~COptimizer() {
	if (genetic_algorithm != nullptr) {
		delete genetic_algorithm;
		genetic_algorithm = nullptr;
	}
}

void COptimizer::vInitialize()
{
	iter = 0;
	d_current_best_fitness = numeric_limits<double>::max();
	initializeAlgorithm();
	genetic_algorithm->initializePopulation();
	genetic_algorithm->evaluatePopulation();
}

void COptimizer::vRunIteration()
{
	iter++;
	genetic_algorithm->runIteration(iter);
	v_current_best = genetic_algorithm->getCurrentBestIndividual().getGenotype();
	d_current_best_fitness = genetic_algorithm->getCurrentBestFitness();
}

void COptimizer::initializeAlgorithm() {
	if (genetic_algorithm == nullptr) {
		genetic_algorithm = new CGeneticAlgorithm(c_evaluator);
	}

	genetic_algorithm->setPopSize(DEFAULT_POP_SIZE);
	genetic_algorithm->setCrossProb(DEFAULT_CROSS_PROB);
	genetic_algorithm->setMutProb(DEFAULT_MUT_PROB);
}

void COptimizer::runAlgorithm(int maxIterations) {
	if (maxIterations < 1) return;

	vInitialize();

	for (int i = 0; i < maxIterations; i++) {
		vRunIteration();
	}

	vector<int> best = *pvGetCurrentBest();

	cout << "The best genotype:\n";
	for (int i = 0; i < best.size(); i++) {
		cout << best[i] << " ";
	}

	cout << "\nFitness: " << getCurrentBestFitness();
}
