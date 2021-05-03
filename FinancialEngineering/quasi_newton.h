#pragma once

#include <optimization.h>

namespace FinancialEngineering
{
	class QuasiNewton : public Optimization, public GradientBasedAlgorithm
	{
	public:
		virtual OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray);
		OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray) override;
	protected:
		Natural _n_par;
		RealArray _x;
		RealVector _gradient;
		RealMatrix _hessian;
		Real _f;
		RealArray _lower;
		RealArray _upper;
		Natural _max_iter;
		Real _tol;

		virtual void update_hessian() = 0;
		virtual void initialize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray);
	};

	inline void QuasiNewton::initialize(SharedPointer<ObjectiveFunction> func, RealArray x, RealArray lower, RealArray upper)
	{
		GradientBasedAlgorithm::initialize(func, lower, upper);
		_x = x;
		_n_par = x.size();
		_f = _func->evaluate(_x);
		_gradient = calculate_gradient(_x, _f);
	}

	inline OptimizationResult QuasiNewton::optimize(SharedPointer<ObjectiveFunction> func, RealArray lower, RealArray upper)
	{
		return optimize(func, (0, 5 * (lower + upper)), lower, upper);
	}
}