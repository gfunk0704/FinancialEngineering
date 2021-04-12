#include <nonparametric_yield_term_structure.h>

namespace FinancialEngineering
{
	YieldPoint::YieldPoint(Date expiry,
				           Real value):
		expiry(expiry),
		value(value)
	{}

	NonparametricYieldTermStructure::NonparametricYieldTermStructure(CurveType type,
															   		 DayCountConvention day_count,
																	 SharedPointer<Calendar> calendar):
		NonparametricYieldTermStructure(type, day_count, calendar, GlobalVariable::get_evaluation_date())

	{}

	NonparametricYieldTermStructure::NonparametricYieldTermStructure(CurveType type,
																	 DayCountConvention day_count, 
		                                                             SharedPointer<Calendar> calendar, 
		                                                             Date value_date,
		                                                             std::vector<YieldPoint> yields) :
		_type(type), 
		_year_fraction(set_year_fraction(day_count)), 
		_calendar(calendar), 
		_value_date(value_date),
		_yields(yields)
	{}

	NonparametricYieldTermStructure::NonparametricYieldTermStructure(CurveType type,
																	 DayCountConvention day_count, 
		                                                             SharedPointer<Calendar> calendar, 
		                                                             Date value_date):
		NonparametricYieldTermStructure(type, day_count, calendar, value_date, std::vector<YieldPoint>())
	{}

	std::ostream& operator<<(std::ostream& os, 
		                     NonparametricYieldTermStructure& term_structure)
	{
		switch (term_structure._type)
		{
		case NonparametricYieldTermStructure::CurveType::PIECEWISE_CONSTANT:
			std::cout << "type :Piecewisw-constant" << std::endl;
		}

		for (std::vector<YieldPoint>::iterator iter = term_structure._yields.begin(); iter != term_structure._yields.end(); iter++)
		{
			std::cout << iter->expiry << ": " << iter->value << std::endl;
		}
		return os;
	}

	PointArray NonparametricYieldTermStructure::get_point_array()
	{
		PointArray point_array;
		for (std::vector<YieldPoint>::iterator iter = _yields.begin(); iter != _yields.end(); iter++)
		{
			point_array.push_back(Point(_year_fraction(_value_date, iter->expiry), iter->value));
		}
		return point_array;
	}

	SharedPointer<Curve> NonparametricYieldTermStructure::create_curve()
	{
		switch (_type)
		{
		case CurveType::PIECEWISE_CONSTANT:
			return SharedPointer<Curve>(new PiecewiseConstantCurve(get_point_array()));
		}
	}
}