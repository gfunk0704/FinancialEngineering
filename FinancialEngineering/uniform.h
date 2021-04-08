#pragma once

#include <rng_64bits.h>
#include <rng_32bits.h>

namespace FinancialEngineering
{
	class RealUniform
	{
	public:
		virtual void reset() = 0;
		virtual Real next_uniform() = 0;
	};

	class RealUniform64 : public RealUniform
	{
	public:
		RealUniform64(SharedPointer<Rng64Bits>);
		void reset() override;
		Real next_uniform() override;
	private:
		SharedPointer<Rng64Bits> _rng;
		union NumericTransform
		{
			NumericTransform(std::uint64_t x)
			{
				i = (UINT64_C(0x3FF) << 52 | x >> 12);
			}
			std::uint64_t i;
			double d;
		};
	};

	inline void RealUniform64::reset()
	{
		_rng->reset();
	}

	inline Real RealUniform64::next_uniform()
	{
		return NumericTransform(_rng->next()).d;
	}

	class RealUniform32 : public RealUniform
	{
	public:
		RealUniform32(SharedPointer<Rng32Bits>);
		void reset() override;
		Real next_uniform() override;
	private:
		SharedPointer<Rng32Bits> _rng;
	};

	inline void RealUniform32::reset()
	{
		_rng->reset();
	}

	inline Real RealUniform32::next_uniform()
	{
		return ((Real)_rng->next()) * 2.32830643653869628906e-010;
	}

	class NaturalUniform
	{
	public:
		NaturalUniform(SharedPointer<Rng32Bits>);
		void reset();
		Natural next_uniform(Natural);
	private:
		SharedPointer<Rng32Bits> _rng;
	};

	inline void NaturalUniform::reset()
	{
		_rng->reset();
	}

	inline Natural NaturalUniform::next_uniform(Natural sup)
	{
		uint32_t divisor = ((-sup) / sup) + 1;
		for (;;) {
			uint32_t value = _rng->next() / divisor;
			if (value < sup)
				return value;
		};
	}
}