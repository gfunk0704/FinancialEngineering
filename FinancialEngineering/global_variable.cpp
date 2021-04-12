
#include <global_variable.h>

namespace FinancialEngineering
{
	Date GlobalVariable::_evaluation_date = boost::gregorian::date(1900, boost::gregorian::Jan, 1);
	Natural GlobalVariable::_seed = 123;
	Natural GlobalVariable::_path = 10000;
}