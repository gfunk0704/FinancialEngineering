#pragma once

#include <simulator_factory.h>
#include <evaluator.h>

namespace FinancialEngineering
{
	class MonteCarloEvaluator : public Evaluator
	{
	public:
		MonteCarloEvaluator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>, Date);
		Real evaluate(SharedPointer<AmericanStyleOption>);

	private:
		Date _end_date;
		SharedPointer<Simulator> _simulator;
		SimulationSample _sample;

		RealArray calculate_expectation(RealVector, RealVector);
	};
}