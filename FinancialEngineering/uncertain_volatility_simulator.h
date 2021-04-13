#pragma once

#include <asset_model.h>
#include <uncertain_volatility.h>
#include <simulator.h>

namespace FinancialEngineering
{
	class UncertainVolatilitySimulator : public Simulator
	{
	public:
		UncertainVolatilitySimulator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>);
		void initialize(Date) override;
		SimulationSample generate_sample() override;
	private:
		SimulationSample _random;
		RealArray _uniform_random;
	};
}
