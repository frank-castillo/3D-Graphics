#include "VariableCache.h"

#include <ImGui/Inc/imgui.h>
#include <algorithm>

VariableCache* VariableCache::Get()
{
	static VariableCache sInstance;
	return &sInstance;
}

void VariableCache::Clear()
{
	mFloatVars.clear();
	mBoolVars.clear();
}

bool VariableCache::IsVarName(const std::string& name) const
{
	return !name.empty() && name[0] == '$';
}

void VariableCache::AddFloat(const std::string& name, float value, float speed, float min, float max)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(mFloatVars.begin(), mFloatVars.end(), [name](auto& var)
	{
		return var.name == name;
	});
	if (iter == mFloatVars.end())
	{
		mFloatVars.emplace_back(FloatVar{ name, value, speed, min, max });
	}
}

float VariableCache::GetFloat(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(mFloatVars.begin(), mFloatVars.end(), [param](auto& var)
		{
			return var.name == param;
		});
		if (iter != mFloatVars.end())
		{
			return (*iter).value;
		}
	}

	return stof(param);
}

void VariableCache::AddBool(const std::string& name, bool value)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(mBoolVars.begin(), mBoolVars.end(), [name](auto& var)
	{
		return var.name == name;
	});
	if (iter == mBoolVars.end())
	{
		mBoolVars.emplace_back(BoolVar{ name, value });
	}
}

bool VariableCache::GetBool(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(mBoolVars.begin(), mBoolVars.end(), [param](auto& var)
		{
			return var.name == param;
		});
		if (iter != mBoolVars.end())
		{
			return (*iter).value;
		}
	}

	return param == "true" ? true : false;
}

void VariableCache::ShowEditor()
{
	if (mFloatVars.empty() && mBoolVars.empty())
		return;

	ImGui::Begin("Variables", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	for (auto& var : mFloatVars)
		ImGui::DragFloat(var.name.c_str(), &var.value, var.speed, var.min, var.max);
	for (auto& var : mBoolVars)
		ImGui::Checkbox(var.name.c_str(), &var.value);
	ImGui::End();
}
