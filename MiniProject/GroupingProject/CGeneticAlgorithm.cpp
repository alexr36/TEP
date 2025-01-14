#include "CGeneticAlgorithm.h"

#include <iostream>

//  ==  Constructors  ==================================================================================================

CGeneticAlgorithm::CGeneticAlgorithm(NGroupingChallenge::CGroupingEvaluator &groupingEvaluator)
    : evaluator(groupingEvaluator) {}


CGeneticAlgorithm::~CGeneticAlgorithm() {}


//  ==  Public methods  ================================================================================================

void CGeneticAlgorithm::initialize() {
    current_best_fitness = std::numeric_limits<double>::max();
}


void CGeneticAlgorithm::run() {
    initializePopulation();
    evaluatePopulation();

    for (int i = 0; i < max_iterations; i++) {
        runIteration(i);
    }

    cout << "Resultant best fitness: " << current_best_individual.getFitness() << endl;
}


void CGeneticAlgorithm::runIteration(int iter) {
    std::cout << "Iteration " << iter << "\n";
    createNextPopulation();
    evaluatePopulation();
}



void CGeneticAlgorithm::printBestSolutionInfo() {
    std::pair<CIndividual, double> result = getBestSolution();

    std::cout << "Current best solution:\n"
        << "Genotype: " << result.first.toString() << "\n"
        << "Fitness: " << result.second << "\n";
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

    auto best_iter = std::min_element(population.begin(), population.end(), compareIndividuals);

    if (best_iter != population.end()) {
        if (current_best_fitness > best_iter->getFitness()) {
            current_best_individual = *best_iter;
            current_best_fitness = current_best_individual.getFitness();
        }
    }

    //std::cout << "Current best fitness: " << current_best_fitness << "\n";
    printBestSolutionInfo();
}


void CGeneticAlgorithm::crossoverPopulation(std::vector<CIndividual>& newPopulation) {

    while (newPopulation.size() < pop_size) {
        CIndividual parent_1 = selectParent();
        CIndividual parent_2 = selectParent();

        pair<CIndividual, CIndividual> children = parent_1.crossover(parent_2, cross_prob);

        addIndividualsToPop(newPopulation, children.first, children.second);
    }
}


void CGeneticAlgorithm::mutatePopulation() {
    if (population.empty()) {
        return;
    }

    for (int i = 0; i < population.size(); i++) {
        population.at(i).mutate(mut_prob, evaluator.iGetUpperBound());
    }
}

/*
 *  1. - Crossover
 *  2. - Evaluation
 *  3. - Mutation
 *  4. - Evaluation
*/
void CGeneticAlgorithm::createNextPopulation() {
    vector<CIndividual> new_population;

    //  1.
    crossoverPopulation(new_population);

    population = new_population;

    //  2.
    evaluatePopulation();

    //  3.
    mutatePopulation();

    //  4.
    //evaluatePopulation();
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

std::pair<CIndividual, double> CGeneticAlgorithm::getBestSolution() const {
    return make_pair(current_best_individual, current_best_fitness);
}


vector<CIndividual>& CGeneticAlgorithm::getPopulation() {
    return population;
}

NGroupingChallenge::CGroupingEvaluator CGeneticAlgorithm::getEvaluator() const {
    return evaluator;
}


//  ==  Setters  =======================================================================================================

void CGeneticAlgorithm::setPopSize(int popSize) {
    pop_size = popSize;
    adjustPopSize(pop_size);
}

void CGeneticAlgorithm::setCrossProb(double crossProb) {
    cross_prob = crossProb;
}

void CGeneticAlgorithm::setMutProb(double mutProb) {
    mut_prob = mutProb;
}


void CGeneticAlgorithm::setMaxIterations(int maxIterations) {
    max_iterations = maxIterations;
}
