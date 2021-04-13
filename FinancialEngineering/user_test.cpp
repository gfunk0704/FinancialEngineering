#include <iostream>

#include <is_weekend.h>
#include <taiwan.h>
#include <deposit_rate.h>
#include <bootstrapper.h>
#include <xorshift32.h>
#include <black_scholes.h>
#include <simulator_factory.h>
#include <monte_carlo_evaluator.h>
#include <american_call_warrant.h>

using namespace FinancialEngineering;

int main()
{
    // set global variable
    GlobalVariable::set_evaluation_date(Date(2021, boost::gregorian::Feb, 26));
    GlobalVariable::set_simulation_path(20000);
    SharedPointer<Rng32Bits> rng = SharedPointer<Rng32Bits>(new Xorwow(GlobalVariable::get_seed()));
    Gaussian::set_method(Gaussian::Method::ZIGGURAT);
    // set TW holidays
    std::vector<IsHoliday> tw_holidays;
    tw_holidays.push_back(is_weekend);
    tw_holidays.push_back(tw_holiday_2021);
    tw_holidays.push_back(tw_holiday_2022);
    SharedPointer<Calendar> tw_calendar = SharedPointer<Calendar>(new Calendar(tw_holidays));
    
    // spot price
    Real spot = 21.25;

    // TAIBOR data
    std::vector<Period> tenor{weeks(1), weeks(2), months(1), months(2), months(3), months(6), months(9), years(1)};
    RealArray value{ 0.0017022,	0.0024033, 0.00386,	0.0043967, 0.0047978, 0.0056867, 0.0070067, 0.0084044 };
    InterestRateQuoteCollection col;
    for (std::size_t i = 0; i < tenor.size(); i++)
    {
        col.push_back(SharedPointer<InterestRateQuote>(new DepositRate(tenor[i], value[i], DayCountConvention::ACT_365_FIXED, tw_calendar, 2)));
    }

    // bootstrapping yiled curve
    SharedPointer<NonparametricYieldTermStructure> term_structure = SharedPointer<NonparametricYieldTermStructure>(new NonparametricYieldTermStructure(NonparametricYieldTermStructure::CurveType::PIECEWISE_CONSTANT, DayCountConvention::ACT_365_FIXED, tw_calendar));
    Bootstrapper::bootstrap(*term_structure, col);
    std::cout << *term_structure << std::endl;

    // B-S model
    SharedPointer<AssetModel> model = SharedPointer<AssetModel>(new BlackScholes(spot, term_structure));
    Parameter bs_par;
    bs_par["sigma"] = 0.2881855;
    model->set_parameter(bs_par);

    // set MC evaluator
    Date end_date = GlobalVariable::get_evaluation_date() + days(50);
    MonteCarloEvaluator evaluator(model, rng, end_date);

    // set instrument
    SharedPointer<AmericanStyleOption> option = SharedPointer<AmericanStyleOption>(new AmericanCallWarrant(tw_calendar, Date(2021, boost::gregorian::Mar, 18), 2, 15.0, 1.0));

    // calculate no-arbitrage price
    Real price = evaluator.evaluate(option);
    std::cout << price << std::endl;

    return 0;
}

