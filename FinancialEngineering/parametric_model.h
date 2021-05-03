#pragma once

#include <global_variable.h>

namespace FinancialEngineering
{
	using Parameter = std::map<std::string, Real>;
	const Real sqrt_double_epsilon = std::sqrt(std::numeric_limits<Real>::epsilon());
	
	class ParametricModel
	{
	public:

		ParametricModel(Date);
		ParametricModel();
		Date get_initial_date();
		virtual SmallNatural n_parameter() = 0;
		void set_parameter(Parameter);
		Parameter get_parameter();
		virtual Real get_initial_value() = 0;
		virtual RealArray parameter_lower() = 0;
		virtual RealArray parameter_upper() = 0;
	protected:
		Date _initial_date;
		RealArray _parameter;
		virtual std::vector<std::string> parameter_name() = 0;
	};

	inline Date ParametricModel::get_initial_date()
	{
		return _initial_date;
	}
}