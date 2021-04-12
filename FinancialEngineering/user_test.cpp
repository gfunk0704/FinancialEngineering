#include <iostream>

#include <is_weekend.h>
#include <taiwan.h>
#include <deposit_rate.h>
#include <bootstrapper.h>
#include <xorshift32.h>
#include <black_scholes.h>
#include <simulator_factory.h>
using namespace FinancialEngineering;

int main()
{
    // set global variable
    GlobalVariable::set_evaluation_date(Date(2021, boost::gregorian::Mar, 25));
    GlobalVariable::set_simulation_path(5);
    SharedPointer<Rng32Bits> rng = SharedPointer<Rng32Bits>(new Xorrow());

    // set TW holidays
    std::vector<IsHoliday> tw_holidays;
    tw_holidays.push_back(is_weekend);
    tw_holidays.push_back(tw_holiday_2021);
    tw_holidays.push_back(tw_holiday_2022);
    SharedPointer<Calendar> tw_calendar = SharedPointer<Calendar>(new Calendar(tw_holidays));
    
    // TAIBOR data
    std::vector<Period> tenor{weeks(1), weeks(2), months(1), months(2), months(3), months(6), months(9), years(1)};
    RealArray value{0.0017078,	0.00241, 0.0038778,	0.0044022, 0.0048, 0.0056889, 0.0070078, 0.0084022};
    InterestRateQuoteCollection col;
    for (std::size_t i = 0; i < tenor.size(); i++)
    {
        col.push_back(SharedPointer<InterestRateQuote>(new DepositRate(tenor[i], value[i], DayCountConvention::ACT_365_FIXED, tw_calendar, 2)));
    }

    // bootstrapping yiled curve
    SharedPointer<NonparametricYieldTermStructure> term_structure = SharedPointer<NonparametricYieldTermStructure>(new NonparametricYieldTermStructure(NonparametricYieldTermStructure::CurveType::PIECEWISE_CONSTANT, DayCountConvention::ACT_365_FIXED, tw_calendar));
    Bootstrapper::bootstrap(*term_structure, col);
    std::cout << *term_structure << std::endl;

    // model calibration
    SharedPointer<AssetModel> bs_model = SharedPointer<AssetModel>(new BlackScholes(100.0, term_structure));
    Parameter bs_par;
    bs_par["sigma"] = 0.15;
    bs_model->set_parameter(bs_par);
    SharedPointer<Simulator> simulator = simulator_factory(bs_model, rng);
    simulator->initialize((GlobalVariable::get_evaluation_date() + days(10)));
    SimulationSample samples = simulator->generate_sample();

    for (SimulationSample::iterator iter = samples.begin(); iter != samples.end(); ++iter)
    {
        std::cout << (*iter).transpose() << std::endl;
    }
    return 0;
}

