#pragma once

#include <uniform.h>

namespace FinancialEngineering
{
	class Gaussian
	{
	public:
		enum class Method
		{
			INVERSE,
			POLAR_REJECTION,
			ZIGGURAT
		};

		static Real next_gaussian(SharedPointer<Rng32Bits>);
		static void set_method(Gaussian::Method);
	private:
		using GaussianRng = Real(*) (SharedPointer<Rng32Bits>);
		static GaussianRng _gaussian_rng;
	};

	inline Real Gaussian::next_gaussian(SharedPointer<Rng32Bits> rng)
	{
		return Gaussian::_gaussian_rng(rng);
	}

	
}