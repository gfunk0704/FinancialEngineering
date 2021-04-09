#pragma once

#include <asset_model.h>
#include <heston.h>
#include <simulator.h>

namespace FinancialEngineering
{
	class HestonSimulator : public Simulator
	{
	public:
		HestonSimulator(SharedPointer<AssetModel>, SharedPointer<Gaussian>);
		void initialize(Date) override;
		SimulationSample generate_sample() override;
	private:
		SharedPointer<Heston> _model;
		SimulationSample _random1;
		SimulationSample _random2;
	};
}
