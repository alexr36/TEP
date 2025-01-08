#include "CIndividual.h"

#include <iostream>

//  ==  Constructors  ==================================================================================================

CIndividual::CIndividual() {
    fitness = INT_MAX;
}

CIndividual::CIndividual(int pointsAmount, int groupsAmount) {
    genotype.resize(pointsAmount);

    for (int &gene : genotype) {
        gene = rand() % groupsAmount + 1;
    }
}

CIndividual::~CIndividual() {}


//  ==  Public methods  ================================================================================================

double CIndividual::calculateFitness(NGroupingChallenge::CGroupingEvaluator &evaluator) {
    fitness = evaluator.dEvaluate(genotype);

    return fitness;
}


void CIndividual::mutate(double mutProb, int groupsAmount) {
    for (int &gene : genotype) {
        if ((double)rand() / RAND_MAX < mutProb) {
            int new_gene = rand() % groupsAmount + 1;

            while (gene == new_gene) {
                new_gene = rand() % groupsAmount + 1;
            }

            gene = new_gene;
        }
    }
}


pair<CIndividual, CIndividual> CIndividual::crossover(const CIndividual &other) {
    CIndividual child_1 = *this;
    CIndividual child_2 = other;

    vector<int> genotypes_combined = combineGenotypes(genotype, other.genotype);

    for (int &gene : genotypes_combined) {
        int child_id = rand() % 2 + 1;

        if (child_id == 1 && child_1.genotype.size() < genotype.size()) {
            child_1.genotype.push_back(gene);
        }
        else if (child_id == 2 && child_2.genotype.size() < genotype.size()) {
            child_2.genotype.push_back(gene);
        }
    }

    return make_pair(child_1, child_2);
}


//  ==  Private methods  ===============================================================================================

vector<int> CIndividual::combineGenotypes(vector<int> genotype_1, vector<int> genotype_2) {
    vector<int> genotypes_combined = genotype_1;
    genotypes_combined.insert(genotypes_combined.end(), genotype_2.begin(), genotype_2.end());

    return genotypes_combined;
}


void CIndividual::printGenotype() {
    for (int &gene : genotype) {
        cout << gene << " ";
    }
    cout << "\n";
}


//  ==  Getters  =======================================================================================================

double CIndividual::getFitness() const {
    return fitness;
}

vector<int> CIndividual::getGenotype() const {
    return genotype;
}
