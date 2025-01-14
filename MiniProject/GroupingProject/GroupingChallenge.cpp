#include "CGeneticAlgorithm.h"
#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "Optimizer.h"

using namespace NGroupingChallenge;

int main()
{
	CGaussianGroupingEvaluatorFactory c_evaluator_factory(5, 100, 5);

	c_evaluator_factory
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0);

	CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

	// COptimizer c_optimizer(*pc_evaluator);
	//
	// c_optimizer.vInitialize();
	//
	// for (int i = 0; i < 10; i++)
	// {
	// 	c_optimizer.vRunIteration();
	// }

	CGeneticAlgorithm ga(*pc_evaluator);
	ga.setPopSize(300);
	ga.setCrossProb(0.84);
	ga.setMutProb(0.17);
	ga.setMaxIterations(10000);
	ga.run();

	delete pc_evaluator;

	return 0;
}