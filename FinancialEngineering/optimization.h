#pragma once

#include <base.h>

namespace FinancialEngineering
{
	class ObjectiveFunction
	{
	public:
		virtual Real evaluate(RealArray) = 0;
	};

	struct OptimizationResult
	{
		OptimizationResult(RealArray par, Real value, Natural iter, unsigned convergence):
			par(par), value(value), iter(iter), convergence(convergence)
		{}

		RealArray par;
		Real value;
		Natural iter;
		SmallNatural convergence;
	};

	class GradientBasedOptimization
	{
	public:
		virtual OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray) = 0;
	};

	class HeristicOptimization
	{
	public:
		virtual OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray) = 0;
	};


}
