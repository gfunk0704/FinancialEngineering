#pragma once

#include <asset_model.h>
#include <gaussian.h>

namespace FinancialEngineering
{
	using SimulationSample = std::vector<RealEigenArray>;

	class Simulator
	{
	public:
		Simulator(SharedPointer<Gaussian>, SharedPointer<NonparametricYieldTermStructure>);
		virtual void initialize(Date) = 0;
		virtual SimulationSample generate_sample() = 0;
	protected:
		const Real dt = 1.0 / 365.0;
		const Real sqrt_dt = std::sqrt(1.0 / 365.0);
		SharedPointer<Gaussian> _gaussian_rng;
		SharedPointer<NonparametricYieldTermStructure> _term_structure;

		SimulationSample generate_random_numbers(Natural);
	};
}