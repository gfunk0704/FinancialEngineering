#pragma once

#include <asset_model.h>
#include <black_scholes.h>
#include <simulator.h>

namespace FinancialEngineering
{
	class BlackScholesSimulator : public Simulator
	{
	public:
		BlackScholesSimulator(SharedPointer<BlackScholes>, SharedPointer<Gaussian>);
		void initialize(Date) override;
		SimulationSample generate_sample() override;
	private:
		SharedPointer<BlackScholes> _model;
		SimulationSample _random;
	};
}
