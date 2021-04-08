#include <rng_64bits.h>

namespace FinancialEngineering
{
	Rng64Bits::Rng64Bits(BigNatural seed):
		_seed(seed)
	{}

	Rng64Bits::Rng64Bits():
		Rng64Bits(GlobalVariable::get_seed())
	{}
}