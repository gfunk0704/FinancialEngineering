#pragma once

#include <quote.h>

namespace FinancialEngineering
{
	template<class Derivative>
	class EquityDerivativeQuote: public Quote
	{
	public:
		EquityDerivativeQuote(Derivative, Real);
		Derivative get_instrument();
	private:
		Derivative _derivative;
	};

}