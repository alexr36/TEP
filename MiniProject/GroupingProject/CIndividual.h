#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H
#include <vector>
#include <string>
#include "GroupingEvaluator.h"


class CIndividual {
public:
    //  Constructors
    CIndividual();
    CIndividual(int pointsAmount, int groupsAmount);

    //  Public methods
    void mutate(double mutProb, int groupsAmount);
    std::pair<CIndividual, CIndividual> crossover(const CIndividual& other, double crossProb);
    double calculateFitness(NGroupingChallenge::CGroupingEvaluator& evaluator);
    std::string toString();

    //  Modyfication
    void mutateAlternative(double mutProb);

    //  Getters
    vector<int>& getGenotype();
    double getFitness() const;

private:
    //  Class fields
    vector<int> genotype;
    double fitness;

    //  Aux methods
    vector<int> combineGenotypes(vector<int> genotype_1, vector<int> genotype_2);
    void printGenotype();
    void swap(int &start_index, int &end_index);
};



#endif //CINDIVIDUAL_H
