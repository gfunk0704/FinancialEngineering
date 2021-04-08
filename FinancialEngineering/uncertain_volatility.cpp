#include <uncertain_volatility.h>

namespace FinancialEngineering
{
	UncertainVolatility::UncertainVolatility(Date initial_date, 
		                                     Real initial_value, 
		                                     SharedPointer<NonparametricYieldTermStructure> term_structure) :
		AssetModel(initial_date, initial_value, term_structure)
	{
		_parameter = RealArray(3);
	}

	UncertainVolatility::UncertainVolatility(Real initial_value,
		                                     SharedPointer<NonparametricYieldTermStructure> term_structure) :
		UncertainVolatility(GlobalVariable::get_evaluation_date(), initial_value, term_structure)
	{}
}