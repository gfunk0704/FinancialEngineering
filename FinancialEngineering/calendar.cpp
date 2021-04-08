#include <calendar.h>

namespace FinancialEngineering
{
	Calendar::Calendar(HolidayList holiday_list):
		_holiday_list(holiday_list)
	{}

	Calendar::Calendar(std::vector<Calendar> calendar_list)
	{
		_holiday_list = HolidayList();
		for (std::vector<Calendar>::iterator calendar_iter = calendar_list.begin(); calendar_iter != calendar_list.end(); calendar_iter++)
		{
			for (HolidayList::iterator iter = (*calendar_iter)._holiday_list.begin(); iter != (*calendar_iter)._holiday_list.end(); iter++)
			{
				_holiday_list.push_back(*iter);
			}
		}
	}

	Date Calendar::convert_tenor_to_date(Date value_date,
		                                 Period period)
	{
		Date expiry = value_date + period;
		if (is_holiday(expiry))
		{
			bool is_yy_or_mm = (period.unit() == Period::TimeUnit::MONTHS || period.unit() == Period::TimeUnit::YEARS);
			bool is_emo = expiry == end_of_month(expiry);
			return shift_n_business_day(expiry, 1, !(is_yy_or_mm && is_emo));
		}
		return expiry;
	}

	Date Calendar::shift_n_business_day(Date date, 
		                                SmallNatural n,
		                                bool is_forward)
	{
		Date target = date;
		while (n > 0)
		{
			target += is_forward ? boost::gregorian::days(1) : boost::gregorian::days(-1);
			if (is_business_day(target))
				n--;
		}
		return target;
	}

	Date Calendar::next_n_business_day(Date date,
		                               SmallNatural n)
	{
		return shift_n_business_day(date, n, true);
	}
	Date Calendar::previous_n_business_day(Date date, SmallNatural n)
	{
		return shift_n_business_day(date, n, false);
	}

	Date Calendar::end_of_month(Date date) 
	{
		Date emo = date.end_of_month();
		while (is_holiday(emo))
		{
			emo -= boost::gregorian::days(1);
		}
		return emo;
	}

	bool Calendar::is_holiday(Date date) 
	{
		for (HolidayList::iterator iter = _holiday_list.begin(); iter != _holiday_list.end(); iter++)
		{
			if ((*iter)(date))
				return true;
		}
		return false;
	}
}