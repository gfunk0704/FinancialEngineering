#pragma once

#include <asset_model.h>
#include <uncertain_volatility.h>
#include <simulator.h>

namespace FinancialEngineering
{
	class UncertainVolatilitySimulator : public Simulator
	{
	public:
		UncertainVolatilitySimulator(SharedPointer<AssetModel>, SharedPointer<Gaussian>, SharedPointer<RealUniform>);
		void initialize(Date) override;
		SimulationSample generate_sample() override;
	private:
		SharedPointer<UncertainVolatility> _model;
		SharedPointer<RealUniform> _uniform_rng;
		SimulationSample _random;
		RealArray _uniform_random;
	};
}
