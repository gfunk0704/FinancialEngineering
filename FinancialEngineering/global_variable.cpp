
#include <global_variable.h>

namespace FinancialEngineering
{
	namespace GlobalVariable
	{
		static Date evaluation_date = boost::gregorian::date(1900, boost::gregorian::Jan, 1);
		static Natural seed = 123;
		static Natural path = 10000;
		static SharedPointer<Rng32Bits> rng = nullptr;

		void set_evaluation_date(Date date)
		{
			evaluation_date = date;
			set_seed(Natural(date.modjulian_day()));
		}

		Date get_evaluation_date()
		{
			return evaluation_date;
		}

		void set_seed(Natural value)
		{
			seed = value;
		}

		Natural GlobalVariable::get_seed()
		{
			return seed;
		}

		void GlobalVariable::set_simulation_path(Natural value)
		{
			path = value;
		}

		Natural GlobalVariable::get_simulation_path()
		{
			return path;
		}

		void GlobalVariable::set_rng(SharedPointer<Rng32Bits> new_rng)
		{
			new_rng.swap(rng);
		}

		SharedPointer<Rng32Bits> GlobalVariable::get_rng()
		{
			return rng->clone_pointer();
		}
	}
}