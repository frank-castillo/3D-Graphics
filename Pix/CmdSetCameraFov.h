#pragma once

#include "Command.h"

class CmdSetCameraFov : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFov";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraFov(float)\n"
			"\n"
			"- Set camera's FOV value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

