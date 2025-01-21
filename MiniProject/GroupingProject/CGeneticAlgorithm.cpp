#include "CGeneticAlgorithm.h"
#include <iostream>
#include "Constants.h"

//  ==  Constructors  ==================================================================================================

CGeneticAlgorithm::CGeneticAlgorithm(NGroupingChallenge::CGroupingEvaluator& groupingEvaluator)
    : evaluator(groupingEvaluator) {
    initialize();
}


//  ==  Public methods  ================================================================================================

void CGeneticAlgorithm::initialize() {
    current_best_fitness = std::numeric_limits<double>::max();
    current_best_individual = CIndividual();
    population.clear();
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

    printBestSolutionInfo();
}


void CGeneticAlgorithm::crossoverPopulation(std::vector<CIndividual>& newPopulation) {

    while (newPopulation.size() < pop_size) {
        CIndividual &parent_1 = selectParent();
        CIndividual &parent_2 = selectParent();

        pair<CIndividual, CIndividual> children = parent_1.crossover(parent_2, cross_prob);

        addIndividualsToPop(newPopulation, children.first, children.second);
    }
}


void CGeneticAlgorithm::mutatePopulation() {
    if (population.empty()) {
        return;
    }

    if ((double)rand() / (double)RAND_MAX < DEFAULT_MUT_TYPE_PROB) {
        for (int i = 0; i < population.size(); i++) {
            population.at(i).mutate(mut_prob, evaluator.iGetUpperBound());
        }
    }
    else {
        for (int i = 0; i < population.size(); i++) {
            population.at(i).mutateAlternative(mut_prob);
        }
    }
}


/*
 *  1. - Crossover
 *  2. - Evaluation
 *  3. - Mutation
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


void CGeneticAlgorithm::addIndividualsToPop(vector<CIndividual>& destination, const CIndividual& individual_1, const CIndividual& individual_2) {
    destination.push_back(individual_1);

    if (destination.size() < pop_size) {
        destination.push_back(individual_2);
    }
}


void CGeneticAlgorithm::pickStartingIndividual() {
    if (population.empty()) return;

    current_best_individual = population[0];
    current_best_fitness = current_best_individual.calculateFitness(evaluator);
}


void CGeneticAlgorithm::adjustPopSize(const int& popSize) {
    pop_size = (popSize % 2 == 0) ? popSize : popSize + 1;
}


bool CGeneticAlgorithm::compareIndividuals(const CIndividual& ind1, const CIndividual& ind2) {
    return ind1.getFitness() < ind2.getFitness();
}


//  ==  Getters  =======================================================================================================

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

double CGeneticAlgorithm::getMutTypeProb() const {
    return mutation_type_prob;
}


//  ==  Setters  =======================================================================================================

void CGeneticAlgorithm::setPopSize(int popSize) {
    if (popSize < 1) pop_size = DEFAULT_POP_SIZE;
    else {
        pop_size = popSize;
        adjustPopSize(pop_size);
    }
}

void CGeneticAlgorithm::setCrossProb(double crossProb) {
    if (crossProb < 0.0) cross_prob = DEFAULT_CROSS_PROB;
    else cross_prob = crossProb;
}

void CGeneticAlgorithm::setMutProb(double mutProb) {
    if (mutProb < 0.0) mut_prob = DEFAULT_MUT_PROB;
    else mut_prob = mutProb;
}

void CGeneticAlgorithm::setMutTypeProb(double mutationTypeProb) {
    if (mutationTypeProb < 0.0) mutation_type_prob = DEFAULT_MUT_TYPE_PROB;
    else mutation_type_prob = mutationTypeProb;
}
