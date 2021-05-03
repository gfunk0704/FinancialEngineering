#pragma once

#include <cir.h>

namespace FinancialEngineering
{
	class AlphaCirZcbClosedForm : public ZcbClosedForm
	{
	public:
		AlphaCirZcbClosedForm(Date, DayCountConvention, RealArray);
		Real evaluate(Real) override;
	};

	class AlphaCir : public Cir
	{
	public:
		AlphaCir(Date, DayCountConvention);
		AlphaCir(DayCountConvention);

		SmallNatural n_parameter() override;
		RealArray parameter_lower() override;
		RealArray parameter_upper() override;
		ShortRateModelType model_type() override;
		SharedPointer<ZcbClosedForm> create_zcb_closed_form() override;
	protected:
		//parameter order: r0, kappa, theta, sigma, sigma_z, alpha
		std::vector<std::string> parameter_name() override;
	};

	SmallNatural AlphaCir::n_parameter()
	{
		return 6;
	}

	RealArray AlphaCir::parameter_lower()
	{
		RealArray boundary(6);
		boundary << Cir::parameter_lower(), sqrt_double_epsilon, 1.0;
		return boundary;
	}

	RealArray AlphaCir::parameter_upper()
	{
		RealArray boundary(6);
		boundary << Cir::parameter_upper(), 1.0, 2.0;
		return boundary;
	}

	ShortRateModel::ShortRateModelType AlphaCir::model_type()
	{
		return ShortRateModelType::ALPHA_CIR;
	}

	std::vector<std::string> AlphaCir::parameter_name()
	{
		std::vector<std::string> name = Cir::parameter_name();
		name.push_back("sigma_z");
		name.push_back("alpha");
		return name;
	}

}