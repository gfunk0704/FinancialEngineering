#include <rng_32bits.h>

namespace FinancialEngineering
{
	Rng32Bits::Rng32Bits(Natural seed) :
		_seed(seed)
	{}

	Rng32Bits::Rng32Bits() :
		Rng32Bits((Natural)GlobalVariable::get_seed())
	{}
}