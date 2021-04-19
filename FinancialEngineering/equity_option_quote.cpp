#include <equity_option_quote.h>

namespace FinancialEngineering
{
	EquityOptionQuote::EquityOptionQuote(SharedPointer<Option> option, 
										 Real premium):
		_option(option),
		_premium(premium)
	{}
}