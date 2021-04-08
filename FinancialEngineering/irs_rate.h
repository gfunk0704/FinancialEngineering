#pragma once

#include <quote.h>
#include <interest_rate_quote.h>
#include <deposit_rate.h>

namespace FinancialEngineering
{
	class IrsRateImpliedQuote : public InterestRateImpliedQuote
	{
	public:
		IrsRateImpliedQuote(Date, DateArray, YearFraction);
		Real evaluate(NonparametricYieldTermStructure) override;
	private:
		RealArray _time_schedule;
		RealArray _tau;
	};

	class IrsRate : public DepositRate
	{
	public:
		IrsRate(Date, Period, Period, Real, DayCountConvention, SharedPointer<Calendar>, SmallNatural);
		SharedPointer<InterestRateImpliedQuote> implied_quote() override;
	private:
		Period _period;
	};
}

