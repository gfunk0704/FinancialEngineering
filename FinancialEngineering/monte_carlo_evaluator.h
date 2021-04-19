#pragma once

#include <simulator_factory.h>
#include <evaluator.h>

namespace FinancialEngineering
{
	class MonteCarloEvaluator : public Evaluator
	{
	public:
		MonteCarloEvaluator(SharedPointer<AssetModel>, Date, bool);
		Real evaluate(SharedPointer<Option>) override;
		RealArray evaluate(std::vector<SharedPointer<Option>>) override;
		void initialize(Date) override;
		void update() override;
	private:
		Date _end_date;
		SharedPointer<Simulator> _simulator;
		SimulationSample _sample;

		Date portfolio_end_date(std::vector<SharedPointer<Option>>);
	};

	inline void MonteCarloEvaluator::initialize(Date end_date)
	{
		_end_date = end_date;
		_simulator->initialize(_end_date);
		update();
	}

	inline void MonteCarloEvaluator::update()
	{
		_sample = _simulator->generate_sample();
	}
}