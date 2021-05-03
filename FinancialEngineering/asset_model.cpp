#include <asset_model.h>

namespace FinancialEngineering
{
	AssetModel::AssetModel(Date initial_date, 
		                   Real initial_value, 
		                   SharedPointer<NonparametricYieldTermStructure> term_structure):
		ParametricModel(initial_date),
		_initial_value(initial_value),
		_term_structure(term_structure)
	{}

	AssetModel::AssetModel(Real initial_value,
						   SharedPointer<NonparametricYieldTermStructure> term_structure):
		AssetModel(GlobalVariable::get_evaluation_date(), initial_value, term_structure)
	{}
}