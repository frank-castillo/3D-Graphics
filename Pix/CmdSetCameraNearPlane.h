#pragma once

#include "Command.h"

class CmdSetCameraNearPlane : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraNearPlane";
	}

	const char* GetDescription() override
	{
		return
			"CmdSetCameraNearPlane(float)\n"
			"\n"
			"- Set camera's near plane value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

