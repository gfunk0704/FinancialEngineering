#include <quote.h>

namespace FinancialEngineering
{
	Quote::Quote(Date value_date, 
		         Real value,
		         SharedPointer<Calendar> calendar):
		_value_date(value_date), 
		_value(value), 
		_calendar(calendar)
	{}

	Quote::Quote(Real value,
				 SharedPointer<Calendar> calendar) :
		Quote(GlobalVariable::get_evaluation_date(), value, calendar)
	{}
}