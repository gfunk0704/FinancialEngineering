#pragma once

#include <parametric_model.h>

namespace FinancialEngineering
{
	class ZcbClosedForm
	{
	public:
		ZcbClosedForm(Date, DayCountConvention);
		virtual Real evaluate(Real) = 0;

		Real evaluate(Date);
		RealArray evaluate(RealArray);
		RealArray evaluate(DateArray);

	protected:
		YearFraction _year_fraction;
		Date _value_date;
	};

	inline Real ZcbClosedForm::evaluate(Real maturity)
	{
		return evaluate(maturity);
	}

	inline RealArray ZcbClosedForm::evaluate(RealArray maturity)
	{
		RealArray d(maturity.size());
		for (Eigen::Index i = 0; i < maturity.size(); i++)
		{
			d(i) = evaluate(maturity(i));
		}
		return d;
	}

	inline Real ZcbClosedForm::evaluate(Date maturity)
	{
		return evaluate(_year_fraction(_value_date, maturity));
	}

	inline RealArray ZcbClosedForm::evaluate(DateArray maturity)
	{
		RealArray d(maturity.size());
		for (Eigen::Index i = 0; i < maturity.size(); i++)
		{
			d(i) = evaluate(maturity[i]);
		}
		return d;
	}

	class ShortRateModel : public ParametricModel
	{
	public:
		enum class ShortRateModelType
		{
			CIR,
			ALPHA_CIR
		};

		ShortRateModel(Date, DayCountConvention);
		ShortRateModel(DayCountConvention);

		virtual SharedPointer<ZcbClosedForm> create_zcb_closed_form() = 0;
		virtual ShortRateModelType model_type() = 0;
	protected:
		DayCountConvention _day_count;
	};
}