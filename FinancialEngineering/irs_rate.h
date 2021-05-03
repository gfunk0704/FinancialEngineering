#pragma once

#include <interest_rate_quote.h>

namespace FinancialEngineering
{
	class IrsRateImpliedQuote : public InterestRateImpliedQuote
	{
	public:
		IrsRateImpliedQuote(Date, DateArray, DateArray, YearFraction);
		Real evaluate(NonparametricYieldTermStructure) override;
	private:
		Real _fixing_time;
		RealArray _expiry_time;
		RealArray _calculation_period;
	};

	inline Real IrsRateImpliedQuote::evaluate(NonparametricYieldTermStructure term_structure)
	{
		YieldCurve yield_curve = term_structure.to_yield_curve();
		Real dominator = (_calculation_period * yield_curve.discount_factor(_expiry_time)).sum();
		return (yield_curve.discount_factor(_fixing_time) - yield_curve.discount_factor(_expiry_time.tail(1)(0))) / dominator;
	}

	class IrsRate : public InterestRateQuote
	{
	public:
		IrsRate(Date, Period, Period, Real, DayCountConvention, SharedPointer<Calendar>, SmallNatural);
		IrsRate(Period, Period, Real, DayCountConvention, SharedPointer<Calendar>, SmallNatural);
		SharedPointer<InterestRateImpliedQuote> implied_quote() override;
		Date expiry_date() override;
	protected:
		Period _tenor;
		Period _period;
		SmallNatural _spot_lag;
	};
}