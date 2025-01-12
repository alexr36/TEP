#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H
#include "CIndividual.h"


class CGeneticAlgorithm {
    public:
        //  Constructors
        CGeneticAlgorithm(int popSize, double crossProb, double mutProb, NGroupingChallenge::CGroupingEvaluator &groupingEvaluator, int maxIterations);
        ~CGeneticAlgorithm();

        //  Public methods
        void initialize();
        void run();

        //  Getters
        int getMaxIterations() const;
        int getPopSize() const;
        double getCrossProb() const;
        double getMutProb() const;
        double getCurrentBestFitness() const;
        CIndividual getCurrentBestIndividual() const;
        vector<CIndividual>& getPopulation();
        NGroupingChallenge::CGroupingEvaluator getEvaluator() const;

    private:
        //  Class fields
        int max_iterations;
        int pop_size;
        double cross_prob;
        double mut_prob;
        double current_best_fitness;
        CIndividual current_best_individual;
        vector<CIndividual> population;
        NGroupingChallenge::CGroupingEvaluator evaluator;

        //  Aux methods
        void initializePopulation();
        void evaluatePopulation();
        void mutatePopulation();
        void createNextPopulation();
        CIndividual& selectParent();
        void addIndividualsToPop(vector<CIndividual> &destination, const CIndividual &individual_1, const CIndividual &individual_2);
        void pickStartingIndividual();
        void adjustPopSize(const int &popSize);
        static bool compareIndividuals(const CIndividual &ind1, const CIndividual &ind2);
};



#endif //CGENETICALGORITHM_H
