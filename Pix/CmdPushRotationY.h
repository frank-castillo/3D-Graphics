#pragma once

#include "Command.h"

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationY (float)\n"
			"\n"
			"- Rotates a matrix by a specific rad value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

