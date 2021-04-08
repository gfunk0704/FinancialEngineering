#pragma once

#include <day_count.h>
#include <quote.h>
#include <nonparametric_yield_term_structure.h>

namespace FinancialEngineering
{
	class InterestRateImpliedQuote
	{
	public:
		virtual Real evaluate(NonparametricYieldTermStructure) = 0;
	};

	class InterestRateQuote : public Quote
	{
	public:
		InterestRateQuote(Date, Real, DayCountConvention, SharedPointer<Calendar>);
		virtual SharedPointer<InterestRateImpliedQuote> implied_quote() = 0;
		virtual Date expiry_date() = 0;
	protected:
		DayCountConvention _day_count;
	};

	
}

