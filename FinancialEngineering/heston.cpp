#include <heston.h>

namespace FinancialEngineering
{
	Heston::Heston(Date initial_date, 
		           Real initial_value, 
		           SharedPointer<NonparametricYieldTermStructure> term_structure) :
		AssetModel(initial_date, initial_value, term_structure)
	{
		_parameter = RealArray(5);
	}

	Heston::Heston(Real initial_value, 
		           SharedPointer<NonparametricYieldTermStructure> term_structure) :
		Heston(GlobalVariable::get_evaluation_date(), initial_value, term_structure)
	{}
}