#pragma once

#include <string>
#include <vector>

class VariableCache
{
public:
	static VariableCache* Get();

public:
	void Clear();

	bool IsVarName(const std::string& name) const;

	void AddFloat(const std::string& name, float value, float speed = 0.01f, float min = -FLT_MAX, float max = FLT_MAX);
	float GetFloat(const std::string& param);

	void AddBool(const std::string& name, bool value);
	bool GetBool(const std::string& param);

	void ShowEditor();

private:
	struct FloatVar
	{
		std::string name;
		float value;
		float speed;
		float min;
		float max;
	};
	struct BoolVar
	{
		std::string name;
		bool value;
	};

	std::vector<FloatVar> mFloatVars;
	std::vector<BoolVar> mBoolVars;
};
