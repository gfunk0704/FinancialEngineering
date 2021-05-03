#include <parametric_model.h>

namespace FinancialEngineering
{
	ParametricModel::ParametricModel(Date initial_date) :
		_initial_date(initial_date)
	{}

	ParametricModel::ParametricModel() :
		ParametricModel(GlobalVariable::get_evaluation_date())
	{}

	Parameter ParametricModel::get_parameter()
	{
		Parameter par;
		std::vector<std::string> par_name = parameter_name();
		for (Size i = 0; i < n_parameter(); i++)
		{
			par[par_name[i]] = _parameter(i);
		}
		return par;
	}

	void ParametricModel::set_parameter(Parameter par)
	{
		std::vector<std::string> par_name = parameter_name();
		for (Size i = 0; i < n_parameter(); i++)
		{
			Parameter::iterator iter = par.find(par_name[i]);
			if (iter != par.end())
				_parameter(i) = iter->second;
		}
	}
}