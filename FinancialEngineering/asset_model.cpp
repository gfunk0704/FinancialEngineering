#include <asset_model.h>

namespace FinancialEngineering
{
	AssetModel::AssetModel(Date initial_date, 
		                   Real initial_value, 
		                   SharedPointer<NonparametricYieldTermStructure> term_structure):
		_initial_date(initial_date),
		_initial_value(initial_value),
		_term_structure(term_structure)
	{}

	AssetModel::AssetModel(Real initial_value,
						   SharedPointer<NonparametricYieldTermStructure> term_structure):
		AssetModel(GlobalVariable::get_evaluation_date(), initial_value, term_structure)
	{}

	Parameter AssetModel::get_parameter()
	{
		Parameter par;
		std::vector<std::string> par_name = parameter_name();
		for (Size i = 0; i < n_parameter(); i++)
		{
			par[par_name[i]] = _parameter[i];
		}
		return par;
	}

	void AssetModel::set_parameter(Parameter par)
	{
		std::vector<std::string> par_name = parameter_name();
		for (Size i = 0; i < n_parameter(); i++)
		{
			Parameter::iterator iter = par.find(par_name[i]);
			if (iter != par.end())
				_parameter[i] = iter->second;
		}
	}
}