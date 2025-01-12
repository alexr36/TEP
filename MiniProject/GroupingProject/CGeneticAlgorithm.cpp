#include "CGeneticAlgorithm.h"

#include <iostream>

//  ==  Constructors  ==================================================================================================

CGeneticAlgorithm::CGeneticAlgorithm(int popSize, double crossProb, double mutProb, NGroupingChallenge::CGroupingEvaluator &groupingEvaluator, int maxIterations)
    : evaluator(groupingEvaluator) {
    cross_prob = crossProb;
    mut_prob = mutProb;
    max_iterations = maxIterations;
    adjustPopSize(popSize);
}


CGeneticAlgorithm::~CGeneticAlgorithm() {}


//  ==  Public methods  ================================================================================================

void CGeneticAlgorithm::initialize() {
    current_best_fitness = std::numeric_limits<double>::max();
}


void CGeneticAlgorithm::run() {
    initializePopulation();
    evaluatePopulation();

    for (int i = 0; i < max_iterations; i++) {
        std::cout << "Iteration " << i << "\n";
        createNextPopulation();
    }

    cout << "Resultant best fitness: " << current_best_individual.getFitness() << endl;
}


//  ==  Private methods  ===============================================================================================

void CGeneticAlgorithm::initializePopulation() {
    population.clear();
    population.reserve(pop_size);

    for (int i = 0; i < pop_size; i++) {
        population.push_back(CIndividual(evaluator.iGetNumberOfPoints(), evaluator.iGetUpperBound()));
    }

    pickStartingIndividual();
}


void CGeneticAlgorithm::evaluatePopulation() {
    if (population.empty()) {
        return;
    }

    for (int i = 0; i < population.size(); i++) {
        population[i].calculateFitness(evaluator);
    }

    auto bestIter = std::min_element(population.begin(), population.end(), compareIndividuals);

    if (bestIter != population.end()) {
        if (current_best_fitness > bestIter->getFitness()) {
            current_best_individual = *bestIter;
            current_best_fitness = current_best_individual.getFitness();
        }
    }

    std::cout << "Current best fitness: " << current_best_fitness << "\n";
}


void CGeneticAlgorithm::mutatePopulation() {
    if (population.empty()) {
        return;
    }

    for (int i = 0; i < population.size(); i++) {
        population.at(i).mutate(mut_prob, evaluator.iGetUpperBound());
    }
}



void CGeneticAlgorithm::createNextPopulation() {
    vector<CIndividual> new_population;

    //  1. - Crossover
    //  2. - Evaluation
    //  3. - Mutation
    //  4. - Evaluation
    while (new_population.size() < pop_size) {
        CIndividual parent_1 = selectParent();
        CIndividual parent_2 = selectParent();

        if ((double)rand() / (double)RAND_MAX < cross_prob) {

            //  1.
            pair<CIndividual, CIndividual> children = parent_1.crossover(parent_2);

            addIndividualsToPop(new_population, children.first, children.second);
        }
        else {
            addIndividualsToPop(new_population, parent_1, parent_2);
        }
    }

    //  2.
    evaluatePopulation();

    //  3.
    mutatePopulation();

    //  4.
    evaluatePopulation();

    population = new_population;
}


CIndividual& CGeneticAlgorithm::selectParent() {
    if (population.empty()) {
        return population[0];
    }

    int parent_1_index = rand() % pop_size;
    int parent_2_index = rand() % pop_size;

    //  The same parent cannot be chosen twice to create a pair
    while (parent_1_index == parent_2_index) {
        parent_2_index = rand() % pop_size;
    }

    return population[parent_1_index].getFitness() <= population[parent_2_index].getFitness()
            ? population[parent_1_index]
            : population[parent_2_index];
}


void CGeneticAlgorithm::addIndividualsToPop(vector<CIndividual> &destination, const CIndividual &individual_1, const CIndividual &individual_2) {
    destination.push_back(individual_1);

    if (destination.size() < pop_size) {
        destination.push_back(individual_2);
    }
}


void CGeneticAlgorithm::pickStartingIndividual() {
    current_best_individual = population[0];
    current_best_fitness = current_best_individual.calculateFitness(evaluator);
}


void CGeneticAlgorithm::adjustPopSize(const int &popSize) {
    pop_size = (popSize % 2 == 0) ? popSize : popSize + 1;
}


bool CGeneticAlgorithm::compareIndividuals(const CIndividual &ind1, const CIndividual &ind2) {
    return ind1.getFitness() < ind2.getFitness();
}


//  ==  Getters  =======================================================================================================

int CGeneticAlgorithm::getMaxIterations() const {
    return max_iterations;
}

int CGeneticAlgorithm::getPopSize() const {
    return pop_size;
}

double CGeneticAlgorithm::getCrossProb() const {
    return cross_prob;
}

double CGeneticAlgorithm::getMutProb() const {
    return mut_prob;
}

double CGeneticAlgorithm::getCurrentBestFitness() const {
    return current_best_fitness;
}

CIndividual CGeneticAlgorithm::getCurrentBestIndividual() const {
    return current_best_individual;
}

vector<CIndividual>& CGeneticAlgorithm::getPopulation() {
    return population;
}

NGroupingChallenge::CGroupingEvaluator CGeneticAlgorithm::getEvaluator() const {
    return evaluator;
}
