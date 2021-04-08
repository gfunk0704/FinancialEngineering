#include <gaussian_inverse.h>

namespace FinancialEngineering
{
    GaussianInverse::GaussianInverse(SharedPointer<RealUniform> uniform):
        _uniform(uniform)
    {}

	Real GaussianInverse::next_gaussian()
	{
		Real r, z;
		Real p = _uniform->next_uniform();
		if (p < 0.0465) {
			r = std::sqrt(std::log(1.0 / (p * p)));
			z = (-1.000182518730158122 * r + 0.029814187308200211 + (4.120411523939115059 * r + 16.682320830719986527) / (r * r + 8.759693508958633869 * r + 7.173787663925508066));
		}
		else if (p > 0.9535) {
			r = std::sqrt(std::log(1.0 / (1.0 - 2.0 * p + p * p)));
			z = -(-1.000182518730158122 * r + 0.029814187308200211 + (4.120411523939115059 * r + 16.682320830719986527) / (r * r + 8.759693508958633869 * r + 7.173787663925508066));
		}
		else {
			Real q = p - 0.5;
			r = q * q;
			z = q * (1.246899760652504 + (0.195740115269792 - 0.652871358365296 * r) / (r * r - 0.839293158122257 * r + 0.155331081623168));
		}
		return z;
	}
}