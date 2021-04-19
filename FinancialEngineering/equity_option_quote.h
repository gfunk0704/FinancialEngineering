#pragma once

#include <option.h>

namespace FinancialEngineering
{
	class EquityOptionQuote 
	{
	public:
		EquityOptionQuote(SharedPointer<Option>, Real);
		SharedPointer<Option> option();
		Real premium();
	private:
		SharedPointer<Option> _option;
		Real _premium;
	};

	inline SharedPointer<Option> EquityOptionQuote::option()
	{
		return _option;
	}

	inline Real EquityOptionQuote::premium()
	{
		return _premium;
	}
}