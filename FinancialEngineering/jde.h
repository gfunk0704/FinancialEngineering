#pragma once

#include <optimization.h>
#include <rng_32bits.h>
#include <uniform.h>
#include <nonreplacement_sampling.h>
#include <global_variable.h>

namespace FinancialEngineering
{

	struct DeSetting
	{
		DeSetting(Real cr_threshold, Real f_lower, Real f_upper, Real f_threshold, Real tol, Natural max_iter, Natural np);
		DeSetting();
		Real cr_threshold;
		Real f_lower;
		Real f_upper;
		Real f_threshold;
		Real tol;
		Natural max_iter;
		Natural np;
	};

	class Jde : public HeristicOptimization
	{
	public:
		Jde(DeSetting);
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
		SharedPointer<Rng32Bits> _rng;
		void pair_sort(RealArray&, std::vector<RealArray>&);
	};

}