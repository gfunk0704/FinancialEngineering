#pragma once

#include <gaussian.h>

namespace FinancialEngineering
{
	class GaussianInverse : public Gaussian
	{
	public:
		GaussianInverse(SharedPointer<RealUniform>);
		void reset() override;
		Real next_gaussian() override;
	private:
		SharedPointer<RealUniform> _uniform;
	};

	inline void GaussianInverse::reset()
	{
		_uniform->reset();
	}
}