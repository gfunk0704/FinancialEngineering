#pragma once

#include <gaussian.h>

namespace FinancialEngineering
{
	class GaussianZiggurat : public Gaussian
	{
	public:
		GaussianZiggurat(SharedPointer<Rng32Bits>);
		void reset() override;
		Real next_gaussian() override;
	private:
		SharedPointer<Rng32Bits> _rng;
		RealUniform32 _uniform;
	};

	inline void GaussianZiggurat::reset()
	{
		_rng->reset();
	}
}