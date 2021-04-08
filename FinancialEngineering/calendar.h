#pragma once

#include <functional>
#include <vector>

#include <date.h>
#include <period.h>
namespace FinancialEngineering 
{
	using IsHoliday = bool(*)(Date&);
	using HolidayList = std::vector<IsHoliday>;

	class Calendar
	{
	public:
		Calendar(HolidayList);
		Calendar(std::vector<Calendar>);

		Date convert_tenor_to_date(Date, Period);
		Date next_n_business_day(Date, SmallNatural);
		Date previous_n_business_day(Date, SmallNatural);
		Date end_of_month(Date);
		bool is_business_day(Date);
		bool is_holiday(Date);
	private:
		friend class Calendar;
		HolidayList _holiday_list;

		Date shift_n_business_day(Date, SmallNatural, bool);
	};

	inline bool Calendar::is_business_day(Date date)
	{
		return (!is_holiday(date));
	}
}