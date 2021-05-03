#pragma once

#include <parametric_model.h>
#include <asset_model.h>
#include <gaussian.h>

namespace FinancialEngineering
{
	using SimulationSample = Eigen::ArrayXXd;

	class Simulator
	{
	public:
		Simulator(SharedPointer<AssetModel>, SharedPointer<Rng32Bits>, bool);
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
		bool _antithetic_variates;

		SimulationSample generate_random_numbers(Natural, Natural, bool);
		SimulationSample generate_random_numbers(Natural);

	};

	inline SimulationSample Simulator::generate_random_numbers(Natural step)
	{
		return generate_random_numbers(step, GlobalVariable::get_simulation_path(), _antithetic_variates);
	}

	inline std::ostream& operator<<(std::ostream& os, SimulationSample& samples)
	{
		os << samples.transpose() << std::endl;
		return os;
	}
}