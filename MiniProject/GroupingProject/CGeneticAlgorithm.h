#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H
#include "CIndividual.h"


class CGeneticAlgorithm {
    public:
        CGeneticAlgorithm(int popSize, double crossProb, double mutProb, NGroupingChallenge::CGroupingEvaluator &groupingEvaluator, int maxIterations);
        ~CGeneticAlgorithm();

        void initialize();
        void run();

        int getMaxIterations() const;
        int getPopSize() const;
        double getCrossProb() const;
        double getMutProb() const;
        double getCurrentBestFitness() const;
        CIndividual getCurrentBestIndividual() const;
        vector<CIndividual> getPopulation() const;
        NGroupingChallenge::CGroupingEvaluator getEvaluator() const;

    private:
        int max_iterations;
        int pop_size;
        double cross_prob;
        double mut_prob;
        double current_best_fitness;
        CIndividual current_best_individual;
        vector<CIndividual> population;
        NGroupingChallenge::CGroupingEvaluator evaluator;

        void initializePopulation();
        void evaluatePopulation();
        void createNextPopulation();
        CIndividual& selectParent();
        void addIndividualsToPop(vector<CIndividual> &destination, CIndividual &individual_1, CIndividual &individual_2);
        void pickStartingIndividual();
        void adjustPopSize(const int &popSize);
};



#endif //CGENETICALGORITHM_H
