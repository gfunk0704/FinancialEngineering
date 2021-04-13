#pragma once

#include <asset_model.h>
#include <heston.h>
#include <simulator.h>

namespace FinancialEngineering
{
	class HestonSimulator : public Simulator
	{
	public:
		HestonSimulator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>);
		void initialize(Date) override;
		SimulationSample generate_sample() override;
	private:
		SimulationSample _random1;
		SimulationSample _random2;
	};
}
