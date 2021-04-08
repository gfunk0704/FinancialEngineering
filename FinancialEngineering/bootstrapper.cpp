#include <bootstrapper.h>

namespace FinancialEngineering
{
	BootstrappingObjectiveFunction::BootstrappingObjectiveFunction(NonparametricYieldTermStructure& term_structure, 
		                                                           SharedPointer<InterestRateQuote> quote):
		_value(quote->value()),
		_implied_quote(quote->implied_quote()),
		_term_structure(term_structure)
	{}

	void Bootstrapper::bootstrap(NonparametricYieldTermStructure& term_structure, 
		                         InterestRateQuoteCollection market_quote_collection)
	{
		Real tol = std::sqrt(std::numeric_limits<Real>::epsilon());
		unsigned i = 0;
		for (InterestRateQuoteCollection::iterator iter = market_quote_collection.begin(); iter != market_quote_collection.end(); iter++)
		{
			term_structure.push_back(YieldPoint((*iter)->expiry_date(), 0.0));
			BootstrappingObjectiveFunction objective_function(term_structure, (*iter));
			std::pair<Real, Real> bounds = boost::math::tools::bisect(objective_function, -0.1, 0.5, [&tol](Real lhs, Real rhs) {return 0.5 * std::abs(lhs + rhs) <= tol; });
			term_structure.update_tail_value(0.5 * (bounds.first + bounds.second));
		}
	}
}