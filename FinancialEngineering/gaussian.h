#pragma once

#include <uniform.h>

namespace FinancialEngineering
{
	class Gaussian
	{
	public:
		virtual void reset() = 0;
		virtual Real next_gaussian() = 0;
	};
}