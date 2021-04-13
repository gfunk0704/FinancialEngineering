#include <nonreplacement_sampling.h>

namespace FinancialEngineering
{

	NaturalArray NonreplacementSampling::sampling(SharedPointer<Rng32Bits> rng,
                                                  Natural size, 
                                                  Natural n)
	{
        // fill the reservoir array
        NaturalArray sample(size);

        for (Natural i = 0; i < size; i++)
            sample[i] = i;

        // replace elements with gradually decreasing probability
        for (Natural i = size; i < n; i++) {
            Natural j = NaturalUniform::next_uniform(rng, i + 1);
            if (j < size)
                sample[j] = i;
        }

        return sample;
	}
}