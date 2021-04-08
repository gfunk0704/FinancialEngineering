#pragma once

#include <piecewise_constant.h>
#include <calendar.h>
#include <day_count.h>
#include <yield_curve.h>

namespace FinancialEngineering 
{
	struct YieldPoint 
	{
		YieldPoint(Date, Real);
		Date expiry;
		Real value;
	};

	class NonparametricYieldTermStructure 
	{
	public:
		enum class CurveType
		{
			PIECEWISE_CONSTANT
		};

		NonparametricYieldTermStructure(CurveType, DayCountConvention, SharedPointer<Calendar>, Date);
		NonparametricYieldTermStructure(CurveType, DayCountConvention, SharedPointer<Calendar>, Date, std::vector<YieldPoint>);
		void push_back(YieldPoint);
		YieldCurve to_yield_curve();

	private:
		friend class Bootstrapper;
		friend class BootstrappingObjectiveFunction;
		friend std::ostream& operator<<(std::ostream&, NonparametricYieldTermStructure&);

		Date _value_date;
		CurveType _type;
		SharedPointer<Calendar> _calendar;
		YearFraction _year_fraction;
		std::vector<YieldPoint> _yields;

		void update_tail_value(Real);
		PointArray get_point_array();
		SharedPointer<Curve> create_curve();
	};

	std::ostream& operator<<(std::ostream&, NonparametricYieldTermStructure&);

	inline void NonparametricYieldTermStructure::push_back(YieldPoint point)
	{
		_yields.push_back(point);
	}

	inline YieldCurve NonparametricYieldTermStructure::to_yield_curve()
	{
		return YieldCurve(_value_date, _year_fraction, create_curve());
	}

	inline void NonparametricYieldTermStructure::update_tail_value(Real value) 
	{
		_yields.back().value = value;
	}
}

