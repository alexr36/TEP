#include "CIndividual.h"

#include <iostream>
#include <sstream>

//  ==  Constructors  ==================================================================================================

CIndividual::CIndividual() {
    fitness = INT_MAX;
}

CIndividual::CIndividual(int pointsAmount, int groupsAmount) {
    genotype.resize(pointsAmount);

    for (int i = 0; i < genotype.size(); i++) {
        genotype[i] = rand() % groupsAmount + 1;
    }
}

CIndividual::~CIndividual() {}


//  ==  Public methods  ================================================================================================

void CIndividual::mutate(double mutProb, int groupsAmount) {
    for (int i = 0; i < genotype.size(); i++) {
        if ((double)rand() / (double)RAND_MAX < mutProb) {
            int new_gene;

            do {
                new_gene = rand() % groupsAmount + 1;
            }
            while (genotype[i] == new_gene);

            genotype[i] = new_gene;
        }
    }
}


pair<CIndividual, CIndividual> CIndividual::crossover(const CIndividual &other, double crossProb) {
    CIndividual child_1 = *this;
    CIndividual child_2 = other;

    if ((double)rand() / (double)RAND_MAX >= crossProb) {
        return make_pair(child_1, child_2);
    }

    vector<int> genotypes_combined = combineGenotypes(genotype, other.genotype);

    for (int i = 0; i < genotypes_combined.size(); i++) {
        int child_id = rand() % 2 + 1;
        int gene = genotypes_combined[i];

        if (child_id == 1 && child_1.genotype.size() < genotype.size()) {
            child_1.genotype.push_back(gene);
        }
        else if (child_id == 2 && child_2.genotype.size() < genotype.size()) {
            child_2.genotype.push_back(gene);
        }
    }

    return make_pair(child_1, child_2);
}


double CIndividual::calculateFitness(NGroupingChallenge::CGroupingEvaluator &evaluator) {
    fitness = evaluator.dEvaluate(genotype);

    return fitness;
}


std::string CIndividual::toString() {
    std::stringstream ss;

    for (int i = 0; i < genotype.size(); i++) {
        ss << genotype[i] << " ";
    }

    return ss.str();
}



//  ==  Private methods  ===============================================================================================

//  Adds two genotype vectors to one bigger genotype vector
vector<int> CIndividual::combineGenotypes(vector<int> genotype_1, vector<int> genotype_2) {
    vector<int> genotypes_combined;
    genotypes_combined.reserve(genotype_1.size() + genotype_2.size());

    genotypes_combined.insert(genotypes_combined.end(), genotype_1.begin(), genotype_1.end());
    genotypes_combined.insert(genotypes_combined.end(), genotype_2.begin(), genotype_2.end());

    return genotypes_combined;
}


void CIndividual::printGenotype() {
    for (int i = 0; i < genotype.size(); i++) {
        cout << genotype[i] << " ";
    }
    cout << "\n";
}


//  ==  Getters  =======================================================================================================

double CIndividual::getFitness() const {
    return fitness;
}

vector<int>& CIndividual::getGenotype() {
    return genotype;
}
