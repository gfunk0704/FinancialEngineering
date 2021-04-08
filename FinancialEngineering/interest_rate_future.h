#pragma once

#include <quote.h>
#include <interest_rate_quote.h>

namespace FinancialEngineering
{
	class InterestRateFuture: public InterestRateQuote
	{
	public:
		InterestRateFuture(Date, Date, Date, Real, DayCountConvention, SharedPointer<Calendar>);
		Date expiry_date() override;
	protected:
		Date _start_date;
		Date _end_date;
	};

	inline Date InterestRateFuture::expiry_date()
	{
		return _end_date;
	}
}