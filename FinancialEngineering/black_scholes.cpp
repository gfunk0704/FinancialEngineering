#include <black_scholes.h>

namespace FinancialEngineering
{
	BlackScholes::BlackScholes(Date initial_date, 
		                       Real initial_value, 
		                       SharedPointer<NonparametricYieldTermStructure> term_structure) :
		AssetModel(initial_date, initial_value, term_structure)
	{
		_parameter = RealArray(1);
	}

	BlackScholes::BlackScholes(Real initial_value,
		                       SharedPointer<NonparametricYieldTermStructure> term_structure) :
		BlackScholes(GlobalVariable::get_evaluation_date(), initial_value, term_structure)
	{}
}