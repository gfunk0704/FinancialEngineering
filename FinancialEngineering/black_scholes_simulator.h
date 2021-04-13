#pragma once

#include <asset_model.h>
#include <black_scholes.h>
#include <simulator.h>

namespace FinancialEngineering
{
	class BlackScholesSimulator : public Simulator
	{
	public:
		BlackScholesSimulator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>);
		void initialize(Date) override;
		SimulationSample generate_sample() override;
	private:
		SimulationSample _random;
	};
}
