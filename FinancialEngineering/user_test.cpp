#include <iostream>

#include <is_weekend.h>
#include <taiwan.h>
#include <deposit_rate.h>
#include <bootstrapper.h>

using namespace FinancialEngineering;

int main()
{
    Date value_date = Date(2021, boost::gregorian::Mar, 25);
    std::vector<IsHoliday> tw_holidays;
    tw_holidays.push_back(is_weekend);
    tw_holidays.push_back(tw_holiday_2021);
    tw_holidays.push_back(tw_holiday_2022);
    SharedPointer<Calendar> tw_calendar = SharedPointer<Calendar>(new Calendar(tw_holidays));
    std::vector<Period> tenor{weeks(1), weeks(2), months(1), months(2), months(3), months(6), months(9), years(1)};
    RealArray value{0.0017078,	0.00241, 0.0038778,	0.0044022, 0.0048, 0.0056889, 0.0070078, 0.0084022};
    InterestRateQuoteCollection col;
    for (std::size_t i = 0; i < tenor.size(); i++)
    {
        col.push_back(SharedPointer<InterestRateQuote>(new DepositRate(value_date, tenor[i], value[i], DayCountConvention::ACT_365_FIXED, tw_calendar, 2)));
    }
    NonparametricYieldTermStructure term_structure(NonparametricYieldTermStructure::CurveType::PIECEWISE_CONSTANT, DayCountConvention::ACT_365_FIXED, tw_calendar, value_date);
    Bootstrapper::bootstrap(term_structure, col);
    std::cout << term_structure << std::endl;
    return 0;
}

