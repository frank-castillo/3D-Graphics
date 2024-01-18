#pragma once

#include "Command.h"

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationX (float)\n"
			"\n"
			"- Rotates a matrix by a specific rad value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

