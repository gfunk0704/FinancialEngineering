#pragma once

#include <simulator_factory.h>
#include <american_style_option.h>

namespace FinancialEngineering
{
	class MonteCarloEvaluator
	{
	public:
		MonteCarloEvaluator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>, Date);
		Real evaluate(SharedPointer<AmericanStyleOption>);

	private:
		Date _end_date;
		SharedPointer<AssetModel> _model;
		SharedPointer<Simulator> _simulator;
		SimulationSample _sample;

		RealArray calculate_expectation(RealVector, RealVector);
	};
}