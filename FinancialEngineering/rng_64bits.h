#pragma once

#include <global_variable.h>

namespace FinancialEngineering
{
	class Rng64Bits
	{
	public:
		Rng64Bits(BigNatural);
		Rng64Bits();
		virtual void reset() = 0;
		virtual BigNatural next() = 0;
	protected:
		BigNatural _seed;
	};
}