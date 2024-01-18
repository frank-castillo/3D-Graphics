#pragma once

#include "Command.h"

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationZ(float)\n"
			"\n"
			"- Rotates a matrix by a specific rad value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

