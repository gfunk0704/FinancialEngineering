#include <lewis_overton.h>

namespace FinancialEngineering
{

	/*
	LewisOverton::LewisOverton(Natural max_iter, Real c0, Real c1):
		LineSearch(max_iter),
		_c0(c0),
		_c1(c1),
		_threshold1(0.0),
		_threshold2(0.0)
	{}

	LewisOverton::LewisOverton():
		LewisOverton(100, 0.0001, 0.9)
	{}

	bool LewisOverton::search(SharedPointer<ObjectiveFunction>, const Real&, const RealArray&, const RealArray&, const RealArray&)
	{
		_alpha = 1.0;
		Real mu = 0.0;
		Real vega;
		bool is_inf = true;

		for (Natural i = 0; i < _max_iter; i++)
		{
			if (calculate_phi(_alpha) > _phi_0 + _alpha * _threshold1)
			{
				vega = _alpha;
				is_inf = false;
			}
			else if (calculate_phi_derivative(_alpha) < _threshold2)
			{
				mu = _alpha;
			}
			else
			{
				return true;
			}
			_alpha = is_inf? (2.0 * _alpha) : 0.5 * (vega + mu);
		}
		return false;
	}
	*/
	
}