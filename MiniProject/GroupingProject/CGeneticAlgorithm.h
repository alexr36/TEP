#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H
#include "CIndividual.h"


class CGeneticAlgorithm {
public:
    //  Constructors
    CGeneticAlgorithm(NGroupingChallenge::CGroupingEvaluator& groupingEvaluator);

    //  Public methods
    void initialize();
    //void run();
    void runIteration(int iter);
    void printBestSolutionInfo();

    void initializePopulation();
    void evaluatePopulation();

    //  Getters
    int getMaxIterations() const;
    int getPopSize() const;
    double getCrossProb() const;
    double getMutProb() const;
    double getCurrentBestFitness() const;
    CIndividual getCurrentBestIndividual() const;
    std::pair<CIndividual, double> getBestSolution() const;
    vector<CIndividual>& getPopulation();
    NGroupingChallenge::CGroupingEvaluator getEvaluator() const;
    double getMutTypeProb() const;

    //  Setters
    void setPopSize(int popSize);
    void setCrossProb(double crossProb);
    void setMutProb(double mutProb);
    void setMutTypeProb(double mutationTypeProb);

private:
    //  Class fields
    int pop_size;
    double cross_prob;
    double mut_prob;
    double current_best_fitness;
    CIndividual current_best_individual;
    vector<CIndividual> population;
    NGroupingChallenge::CGroupingEvaluator &evaluator;
    double mutation_type_prob;

    //  Aux methods
    void crossoverPopulation(std::vector<CIndividual>& newPopulation);
    void mutatePopulation();
    void createNextPopulation();
    CIndividual& selectParent();
    void addIndividualsToPop(vector<CIndividual>& destination, const CIndividual& individual_1, const CIndividual& individual_2);
    void pickStartingIndividual();
    void adjustPopSize(const int& popSize);
    static bool compareIndividuals(const CIndividual& ind1, const CIndividual& ind2);
};


#endif //CGENETICALGORITHM_H
