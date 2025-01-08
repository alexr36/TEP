#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H
#include <vector>
#include "GroupingEvaluator.h"


class CIndividual {
    public:
        CIndividual();
        CIndividual(int pointsAmount, int groupsAmount);
        ~CIndividual();

        void mutate(double mutProb, int groupsAmount);
        std::pair<CIndividual, CIndividual> crossover(const CIndividual& other);

        double calculateFitness(NGroupingChallenge::CGroupingEvaluator &evaluator);

        vector<int> getGenotype() const;
        double getFitness() const;

    private:
        vector<int> genotype;
        double fitness;

        vector<int> combineGenotypes(vector<int> genotype_1, vector<int> genotype_2);
        void printGenotype();
};



#endif //CINDIVIDUAL_H
