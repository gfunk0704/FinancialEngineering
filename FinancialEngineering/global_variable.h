#pragma once

#include <date.h>
#include <day_count.h>

namespace FinancialEngineering
{
	class GlobalVariable
	{
	public:
		static void set_evaluation_date(Date);
		static Date get_evaluation_date();
		static void set_seed(BigNatural);
		static BigNatural get_seed();
		static void set_simulation_path(Natural);
		static Natural get_simulation_path();
	private:
		static Date _evaluation_date;
		static BigNatural _seed;
		static Natural _path;
	};

	inline void GlobalVariable::set_evaluation_date(Date date)
	{
		_evaluation_date = date;
		set_seed(BigNatural(date.modjulian_day()));
	}

	inline Date GlobalVariable::get_evaluation_date()
	{
		return _evaluation_date;
	}

	inline void GlobalVariable::set_seed(BigNatural seed)
	{
		_seed = seed;
	}

	inline BigNatural GlobalVariable::get_seed()
	{
		return _seed;
	}

	inline void GlobalVariable::set_simulation_path(Natural path)
	{
		_path = path;
	}

	inline Natural GlobalVariable::get_simulation_path()
	{
		return _path;
	}
}