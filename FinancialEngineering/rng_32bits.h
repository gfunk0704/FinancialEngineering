#pragma once

#include <global_variable.h>

namespace FinancialEngineering
{
	class Rng32Bits
	{
	public:
		Rng32Bits(Natural);
		Rng32Bits();
		virtual void reset() = 0;
		virtual Natural next() = 0;
	protected:
		Natural _seed;
	};
}