#include <nonreplacement_sampling.h>

namespace FinancialEngineering
{
	NonreplacementSampling::NonreplacementSampling(NaturalUniform uniform):
		_uniform(uniform)
	{}

	NaturalArray NonreplacementSampling::sampling(Natural size, 
                                                  Natural n)
	{
        // fill the reservoir array
        NaturalArray sample(size);

        for (Natural i = 0; i < size; i++)
            sample[i] = i;

        // replace elements with gradually decreasing probability
        for (Natural i = size; i < n; i++) {
            Natural j = _uniform.next_uniform(i + 1);
            if (j < size)
                sample[j] = i;
        }

        return sample;
	}
}