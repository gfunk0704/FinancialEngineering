#include <taiwan.h>

namespace FinancialEngineering
{
	bool tw_holiday_2021(Date& date)
	{
		auto dd = date.day().as_number();

		switch (date.month())
		{
		case boost::gregorian::Jan:
			return (dd == 1);
		case boost::gregorian::Feb:
			return (dd >= 10 && dd <= 16);
		case boost::gregorian::Mar:
			return (dd == 1);
		case boost::gregorian::Apr:
			return (dd == 2 || dd == 5 || dd == 30);
		case boost::gregorian::Jun:
			return (dd == 14);
		case boost::gregorian::Sep:
			return (dd == 20 || dd == 21);
		case boost::gregorian::Oct:
			return (dd == 11);
		case boost::gregorian::Dec:
			return (dd == 31);
		}
		return false;
	}

	bool tw_holiday_2022(Date& date)
	{
		auto dd = date.day().as_number();

		switch (date.month())
		{
		case boost::gregorian::Jan:
			return (dd == 31);
		case boost::gregorian::Feb:
			return ((dd >= 1 && dd <= 4) || dd == 28);
		case boost::gregorian::Apr:
			return (dd == 4 || dd == 5);
		case boost::gregorian::May:
			return (dd == 2);
		case boost::gregorian::Jun:
			return (dd == 3);
		case boost::gregorian::Sep:
			return (dd == 9);
		case boost::gregorian::Oct:
			return (dd == 10);
		}
		return false;
	}
}