#pragma once

#include <asset_model.h>
#include <gaussian.h>

namespace FinancialEngineering
{
	using SimulationSample = std::vector<RealEigenArray>;

	class Simulator
	{
	public:
		Simulator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>);
		virtual void initialize(Date);
		virtual SimulationSample generate_sample() = 0;
	protected:
		const Real dt = 1.0 / 365.0;
		const Real sqrt_dt = std::sqrt(1.0 / 365.0);
		Natural _n_step;
		RealArray _rt;
		SharedPointer<AssetModel> _model;
		SharedPointer<Rng32Bits> _rng;

		SimulationSample generate_random_numbers(Natural);
	};

	inline std::ostream& operator<<(std::ostream& os, SimulationSample& samples)
	{
		for (SimulationSample::iterator iter = samples.begin(); iter != samples.end(); ++iter)
		{
			os << (*iter).transpose() << std::endl;
		}
		return os;
	}
}