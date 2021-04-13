#pragma once

#include <asset_model.h>
#include <instrument.h>
#include <option.h>
#include <american_style_option.h>

namespace FinancialEngineering
{
	class Evaluator
	{
	public:
		Evaluator(SharedPointer<AssetModel>);
		virtual Real evaluate(SharedPointer<AmericanStyleOption>) = 0;
		SharedPointer<AssetModel> get_model();
	protected:
		SharedPointer<AssetModel> _model;
	};

	inline SharedPointer<AssetModel> Evaluator::get_model()
	{
		return _model;
	}
}