#pragma once

#include <optimization.h>

namespace FinancialEngineering
{
	/*
	class GradientBasedOptimization : public Optimization, public GradientBasedAlgorithm
	{
	public:
		virtual OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray) = 0;
		OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray) override;
	protected:
		Natural _n_par;
		RealArray _x;
		RealVector _gradient;
		Real _f;
		RealArray _lower;
		RealArray _upper;

		virtual void initialize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray);
	};

	inline void GradientBasedOptimization::initialize(SharedPointer<ObjectiveFunction> func, RealArray x, RealArray lower, RealArray upper)
	{
		GradientBasedAlgorithm::initialize(func, lower, upper);
		_x = x;
		_n_par = x.size();
		_f = _func->evaluate(_x);
		_gradient = calculate_gradient(_x, _f);
	}

	inline OptimizationResult GradientBasedOptimization::optimize(SharedPointer<ObjectiveFunction> func, RealArray lower, RealArray upper)
	{
		return optimize(func, (0, 5 * (lower + upper)), lower, upper);
	}
	*/
	
}