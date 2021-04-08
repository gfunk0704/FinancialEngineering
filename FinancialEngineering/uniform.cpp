#include <uniform.h>

namespace FinancialEngineering
{
	
	RealUniform64::RealUniform64(SharedPointer<Rng64Bits> rng):
		_rng(rng)
	{}

	RealUniform32::RealUniform32(SharedPointer<Rng32Bits> rng):
		_rng(rng)
	{}
	
	NaturalUniform::NaturalUniform(SharedPointer<Rng32Bits> rng) :
		_rng(rng)
	{}
}