#pragma once

#include <population_based_optimization.h>
#include <nonreplacement_sampling.h>


namespace FinancialEngineering
{

	struct JdeSetting
	{
		JdeSetting(Real, Real, Real, Real, Real, Natural, Natural);
		JdeSetting();
		Real cr_threshold;
		Real f_lower;
		Real f_upper;
		Real f_threshold;
		Real tol;
		Natural max_iter;
		Natural np;
	};

	class Jde : public PopulationBasedOptimization
	{
	public:
		Jde(JdeSetting);
		Jde();
		virtual OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray) override;
	protected:
		Real _cr_threshold;
		Real _f_threshold;
		Real _f_lower;
		Real _f_range;
		Real _tol;
		Natural _max_iter;
		Natural _np;
		void pair_sort(RealArray&, std::vector<RealArray>&);
	};

}