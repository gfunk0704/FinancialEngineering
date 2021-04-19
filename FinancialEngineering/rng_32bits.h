#pragma once

#include <base.h>

namespace FinancialEngineering
{
	class Rng32Bits
	{
	public:
		Rng32Bits(Natural);
		virtual SharedPointer<Rng32Bits> clone_pointer() = 0;
		virtual void reset() = 0;
		virtual Natural next() = 0;
		virtual void status() = 0;
	protected:
		Natural _seed;
	};
}