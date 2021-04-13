#pragma once

#include <optimization.h>
#include <rng_32bits.h>
#include <uniform.h>
#include <nonreplacement_sampling.h>

namespace FinancialEngineering
{

	struct JdeSetting
	{
		JdeSetting(Real cr_threshold, Real f_lower, Real f_upper, Real f_threshold, Real tol, Natural max_iter, Natural np);
		JdeSetting();
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
		Jde(SharedPointer<Rng32Bits>, JdeSetting);
		Jde(SharedPointer<Rng32Bits>);
		OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray) override;
	private:
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

	inline void Jde::pair_sort(RealArray& value, std::vector<RealArray>& samples)
	{
		using SamplePair = std::pair<Real, RealArray>;
		std::vector<SamplePair> sample_pair;
		for (Size i = 0; i < value.size(); i++)
			sample_pair.push_back(std::make_pair(value[i], samples[i]));

		std::sort(sample_pair.begin(), sample_pair.end());

		for (Size i = 0; i < value.size(); i++)
		{
			value[i] = sample_pair[i].first;
			samples[i] = sample_pair[i].second;
		}
	}
}