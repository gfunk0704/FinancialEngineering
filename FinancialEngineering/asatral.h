#pragma once

#include <optimization.h>

namespace FinancialEngineering
{
	class Asatral : public GradientBasedOptimization
	{
	private:
		RealMatrix _hessian;
		RealVector _gradient;
		RealArray _x;
		RealArray _beta;
		RealArray _sigma;
		Real _delta0;
		Real _tau0;
		Real _gamma;
		Real _max_iter;

		Real infinity_norm(RealArray);
	};

	inline Real Asatral::infinity_norm(RealArray v)
	{
		return v.abs().maxCoeff();
	}
}