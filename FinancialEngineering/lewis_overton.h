#pragma once

#include <line_search.h>

namespace FinancialEngineering
{

	/*
	class LewisOverton : public LineSearch
	{
	public:
		LewisOverton(Natural, Real, Real);
		LewisOverton();

		bool search(SharedPointer<ObjectiveFunction>, const Real&, const RealArray&, const RealArray&, const RealArray&) override;
	private:
		Real _c0;
		Real _c1;
		Real _threshold1;
		Real _threshold2;

		void initialize(SharedPointer<ObjectiveFunction>, const RealArray&, const RealArray&, const RealArray&, const RealVector&) override;
	};

	inline void LewisOverton::initialize(SharedPointer<ObjectiveFunction> func, const RealArray& lower, const RealArray& upper, const RealArray& x, const RealVector& g)
	{
		LineSearch::initialize(func, lower, upper, x, g);
		_threshold1 = _c0 * _phi_derivative_0;
		_threshold2 = _c1 * _phi_derivative_0;
	}
	*/
	
}
