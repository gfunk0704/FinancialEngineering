#pragma once

#include <quote.h>
#include <interest_rate_quote.h>

namespace FinancialEngineering
{
	class DepositRateImpliedQuote : public InterestRateImpliedQuote
	{
	public:
		DepositRateImpliedQuote(Date, Date, Date, YearFraction);
		Real evaluate(NonparametricYieldTermStructure) override;
		Real evaluate(SharedPointer<ZcbClosedForm>) override;

	private:
		Real _fixing_time;
		Real _expiry_time;
		Real _calculation_period;
	};

	inline Real DepositRateImpliedQuote::evaluate(NonparametricYieldTermStructure term_structure)
	{
		YieldCurve yield_curve = term_structure.to_yield_curve();
		return (yield_curve.discount_factor(_fixing_time) / yield_curve.discount_factor(_expiry_time) - 1.0) / _calculation_period;
	}

	inline Real DepositRateImpliedQuote::evaluate(SharedPointer<ZcbClosedForm> zcb_closed_form)
	{
		return (zcb_closed_form->evaluate(_fixing_time) / zcb_closed_form->evaluate(_expiry_time) - 1.0) / _calculation_period;
	}

	class DepositRate : public InterestRateQuote
	{
	public:
		DepositRate(Date, Period, Real, DayCountConvention, SharedPointer<Calendar>, SmallNatural);
		DepositRate(Period, Real, DayCountConvention, SharedPointer<Calendar>, SmallNatural);
		SharedPointer<InterestRateImpliedQuote> implied_quote() override;
		Date expiry_date() override;
	protected:
		Period _tenor;
		SmallNatural _spot_lag;
	};

	inline Date DepositRate::expiry_date()
	{
		return _calendar->convert_tenor_to_date(_value_date, _tenor);
	}

	inline SharedPointer<InterestRateImpliedQuote> DepositRate::implied_quote()
	{
		Date fixing_date = _calendar->next_n_business_day(_value_date, _spot_lag);
		Date expiry_date = _calendar->convert_tenor_to_date(_value_date, _tenor);
		return SharedPointer<InterestRateImpliedQuote>(new DepositRateImpliedQuote(_value_date, fixing_date, expiry_date, set_year_fraction(_day_count)));
	}
}

