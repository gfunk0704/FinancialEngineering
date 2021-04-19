#pragma once

#include <uniform.h>

namespace FinancialEngineering
{
	namespace Gaussian
	{
		enum class Method
		{
			INVERSE,
			POLAR_REJECTION,
			ZIGGURAT
		};

		Real next_gaussian(SharedPointer<Rng32Bits>);
		void set_method(Method);
	}
}