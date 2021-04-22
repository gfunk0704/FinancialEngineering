#pragma once

#include <optimization.h>

namespace FinancialEngineering
{
	/*
	class LineSearch : public GradientBasedAlgorithm
	{
	public:
		LineSearch(Natural);
		virtual bool search(SharedPointer<ObjectiveFunction>, const Real&, const RealArray&, const RealArray&, const RealArray&) = 0;
		Real get_alpha();

	protected:
		SharedPointer<ObjectiveFunction> _func;
		RealArray _x;
		RealArray _g;
		Natural _max_iter;
		Real _alpha;
		Real _phi_0;
		Real _phi_derivative_0;

		virtual void initialize(SharedPointer<ObjectiveFunction>, const RealArray&, const RealArray&, const RealArray&, const RealVector&);
		Real calculate_phi(Real);
		Real calculate_phi_derivative(Real);

	};

	inline void LineSearch::initialize(SharedPointer<ObjectiveFunction> func, const RealArray& lower, const RealArray&  upper, const RealArray& x, const RealVector& g)
	{
		GradientBasedAlgorithm::initialize(func, lower, upper);
		_x = x;
		_g = g.array();
		_phi_0 = calculate_phi(0.0);
		_phi_derivative_0 = calculate_phi_derivative(0.0);
	}

	inline Real LineSearch::get_alpha()
	{
		return _alpha;
	}

	inline Real LineSearch::calculate_phi(Real alpha)
	{
		return _func->evaluate(projection(_x + alpha * _g));
	}

	inline Real LineSearch::calculate_phi_derivative(Real alpha)
	{
		return (calculate_phi_derivative(alpha + _h) - calculate_phi_derivative(alpha - _h)) / _h2;
	}
	*/
	
}