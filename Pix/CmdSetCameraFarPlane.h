#pragma once

#include "Command.h"

class CmdSetCameraFarPlane : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFarPlane";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraFarPlane(float)\n"
			"\n"
			"- Set camera's far plane value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

