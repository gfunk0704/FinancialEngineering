#pragma once

#include <cmath>
#include <limits>

#include <boost/math/tools/roots.hpp>

#include <interest_rate_quote.h>
#include <nonparametric_yield_term_structure.h>

namespace FinancialEngineering
{
	using  InterestRateQuoteCollection = std::vector<SharedPointer<InterestRateQuote>>;

	class BootstrappingObjectiveFunction
	{
	public:
		BootstrappingObjectiveFunction(NonparametricYieldTermStructure&, SharedPointer<InterestRateQuote>);
		Real operator()(Real);
	private:
		Real _value;
		NonparametricYieldTermStructure& _term_structure;
		SharedPointer<InterestRateImpliedQuote> _implied_quote;
	};

	inline Real BootstrappingObjectiveFunction::operator()(Real guess)
	{
		_term_structure.update_tail_value(guess);
		return _implied_quote->evaluate(_term_structure) - _value;
	}

	class Bootstrapper
	{
	public:
		static void bootstrap(NonparametricYieldTermStructure&, InterestRateQuoteCollection);
	};
}