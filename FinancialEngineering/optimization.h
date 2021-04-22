#pragma once

#include <iostream>

#include <base.h>
#include <boost/math/tools/minima.hpp>

namespace FinancialEngineering
{
	class ObjectiveFunction
	{
	public:
		virtual Real evaluate(const RealArray&) = 0;
		virtual bool update_gradient(const RealArray&);
		virtual RealVector gradient();
	protected:
		RealVector _gradient = RealVector();
	};

	inline bool ObjectiveFunction::update_gradient(const RealArray& x)
	{
		return false;
	}

	inline RealVector ObjectiveFunction::gradient()
	{
		return _gradient;
	}

	struct OptimizationResult
	{
		OptimizationResult(RealArray, Real, Natural, unsigned);

		RealArray par;
		Real value;
		Natural iter;
		SmallNatural convergence;
	};

	class Optimization
	{
	public:
		virtual OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray) = 0;
	};

	/*
	class GradientBasedAlgorithm
	{
	protected:
		SharedPointer<ObjectiveFunction> _func;
		RealArray _lower;
		RealArray _upper;
		const Real _h = std::sqrt(std::numeric_limits<Real>::epsilon());
		const Real _h2 = 2.0 * std::sqrt(std::numeric_limits<Real>::epsilon());

		void initialize(SharedPointer<ObjectiveFunction>, const RealArray&, const RealArray&);
		RealArray projection(RealArray);
		RealVector calculate_gradient(const RealArray&, const Real&);
		RealVector numerical_gradient(const RealArray&, const Real&);
	};

	inline void GradientBasedAlgorithm::initialize(SharedPointer<ObjectiveFunction> func, const RealArray& lower, const RealArray& upper)
	{
		_func = func;
		_lower = lower;
		_upper = upper;
	}

	inline RealArray GradientBasedAlgorithm::projection(RealArray z)
	{
		return z.max(_lower).min(_upper);
	}
	*/
	
}
