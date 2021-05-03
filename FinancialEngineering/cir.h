#pragma once

#include <parametric_model.h>
#include <short_rate_model.h>

namespace FinancialEngineering
{
	class CirZcbClosedForm : public ZcbClosedForm
	{
	public:
		CirZcbClosedForm(Date, DayCountConvention, RealArray);
		Real evaluate(Real) override;
	private:
		Real _x0;
		Real _power;
		Real _h;
		Real _h2;
		Real _kappa_h;
	};

	inline Real CirZcbClosedForm::evaluate(Real maturity)
	{
		Real exp_term = std::exp(maturity * _h) - 1;
		Real dominator = _h2 + _kappa_h * exp_term;
		Real b = (2.0 * exp_term) / dominator;
		Real a = std::pow(_h2 * std::exp(0.5 * _kappa_h * maturity) / dominator, _power);
		return a * std::exp(-b * _x0);
	}

	class Cir : public ShortRateModel
	{
	public:
		Cir(Date, DayCountConvention);
		Cir(DayCountConvention);

		virtual SmallNatural n_parameter() override;
		virtual RealArray parameter_lower() override;
		virtual RealArray parameter_upper() override;
		virtual ShortRateModelType model_type() override;
		virtual Real get_initial_value() override;
		virtual SharedPointer<ZcbClosedForm> create_zcb_closed_form() override;
	protected:
		//parameter order: r0, kappa, theta, sigma
		virtual std::vector<std::string> parameter_name() override;

		SharedPointer<ZcbClosedForm> create_zcb_closed_form(RealArray);
	};

	inline SmallNatural Cir::n_parameter()
	{
		return 4;
	}

	inline RealArray Cir::parameter_lower()
	{
		return RealArray::Constant(4, sqrt_double_epsilon);
	}

	inline RealArray Cir::parameter_upper()
	{
		RealArray boundary(4);
		boundary << 1.0, 3.0, 1.0, 1.0;
		return boundary;
	}

	inline ShortRateModel::ShortRateModelType Cir::model_type()
	{
		return ShortRateModel::ShortRateModelType::CIR;
	}

	inline Real Cir::get_initial_value()
	{
		return _parameter(0);
	}

	inline std::vector<std::string> Cir::parameter_name()
	{
		return std::vector<std::string>{"r0", "kappa", "theta", "sigma"};
	}

	inline SharedPointer<ZcbClosedForm> Cir::create_zcb_closed_form()
	{
		return create_zcb_closed_form(_parameter);
	}

	inline SharedPointer<ZcbClosedForm> Cir::create_zcb_closed_form(RealArray par)
	{
		return SharedPointer<ZcbClosedForm>(new CirZcbClosedForm(_initial_date, _day_count, par));
	}
}