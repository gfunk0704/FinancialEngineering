#include <iostream>

#include <is_weekend.h>
#include <taiwan.h>
#include <deposit_rate.h>
#include <bootstrapper.h>
#include <xorshift32.h>
#include <black_scholes.h>
#include <heston.h>
#include <simulator_factory.h>
#include <monte_carlo_evaluator.h>
#include <american_style_option.h>
#include <european_style_option.h>
#include <calibration.h>
#include <equity_option_quote.h>

using namespace FinancialEngineering;

int main()
{
    // set global variable
    GlobalVariable::initialize_n_threads(2);
    GlobalVariable::set_evaluation_date(Date(2021, boost::gregorian::Feb, 26));
    GlobalVariable::set_simulation_path(12000);
    GlobalVariable::set_rng(SharedPointer<Rng32Bits>(new Xorwow()));
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
    std::vector<Real> value{ 0.0017022,	0.0024033, 0.00386,	0.0043967, 0.0047978, 0.0056867, 0.0070067, 0.0084044 };
    InterestRateQuoteCollection col;
    for (std::size_t i = 0; i < tenor.size(); i++)
    {
        col.push_back(SharedPointer<InterestRateQuote>(new DepositRate(tenor[i], value[i], DayCountConvention::ACT_365_FIXED, tw_calendar, 2)));
    }

    // bootstrapping yiled curve
    SharedPointer<NonparametricYieldTermStructure> term_structure = SharedPointer<NonparametricYieldTermStructure>(new NonparametricYieldTermStructure(NonparametricYieldTermStructure::CurveType::PIECEWISE_CONSTANT, DayCountConvention::ACT_365_FIXED, tw_calendar));
    Bootstrapper::bootstrap(*term_structure, col);
    std::cout << *term_structure << std::endl;

    // set model
    SharedPointer<AssetModel> model = SharedPointer<AssetModel>(new Heston(spot, term_structure));
    
    // set MC evaluator
    Date end_date = GlobalVariable::get_evaluation_date();
    SharedPointer<Evaluator> evaluator = SharedPointer<Evaluator>(new MonteCarloEvaluator(model, end_date + days(1), true));

    // set instrument
    std::vector<Real> strike{ 18.5, 25.0, 22.0, 17.5, 19.5, 16, 21.0 ,19.0, 20.0, 20.0, 21.0 };
    std::vector<Real> premium{ 2.83, 1.07, 1.75, 2.57, 2.69, 3.23, 1.72, 2.62, 3.35, 3.11, 2.52 };
    std::vector<Real> leverage{ 1.0, 1.0, 1.0, 0.6, 1.0, 0.6, 1.0, 1.0, 1.0, 1.0, 1.0 };
    DateArray expiry{ Date(2021, boost::gregorian::Mar, 22),
                      Date(2021, boost::gregorian::Aug, 19),
                      Date(2021, boost::gregorian::Jul, 22),
                      Date(2021, boost::gregorian::Jul, 27),
                      Date(2021, boost::gregorian::Jun, 21),
                      Date(2021, boost::gregorian::Apr, 21),
                      Date(2021, boost::gregorian::Apr, 26),
                      Date(2021, boost::gregorian::Apr, 6),
                      Date(2021, boost::gregorian::Oct, 28),
                      Date(2021, boost::gregorian::Aug, 23) };

    OptionCollection option_col;

    for (Size i = 0; i < expiry.size(); i++)
    {
        SharedPointer<OptionPayoff> call_warrant_payoff = SharedPointer<OptionPayoff>(new WarrantPayoff(OptionPayoff::Type::CALL, strike[i], leverage[i]));
        SharedPointer<Option> option = SharedPointer<Option>(new AmericanStyleOption(tw_calendar, expiry[i], 2, call_warrant_payoff));
        option_col.push_back(EquityOptionQuote(option, premium[i]));
    }

    CalibrationResult result = calibrate(evaluator, option_col);
    std::cout << "calibration result" << std::endl;
    std::cout << "RMSE: " << result.result1.value << std::endl;
    std::cout << "iteration: " << result.result1.iter << std::endl;
    std::cout << "par: "  << std::endl;
    Parameter par = result.model->get_parameter();
    for (Parameter::iterator iter = par.begin(); iter != par.end(); ++iter)
    {
        std::cout << (*iter).first << ": " << (*iter).second << std::endl;
    }
    return 0;
}

