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
		virtual Real evaluate(SharedPointer<Option>) = 0;
		virtual RealArray evaluate(std::vector<SharedPointer<Option>>) = 0;
		virtual void initialize(Date) = 0;
		virtual void update() = 0;
		SharedPointer<AssetModel> get_model();
	protected:
		SharedPointer<AssetModel> _model;
	};

	inline SharedPointer<AssetModel> Evaluator::get_model()
	{
		return _model;
	}
}