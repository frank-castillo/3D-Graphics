#pragma once

#include "Command.h"

class CmdSetCameraDirection : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraDirection";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraDirection(x, y, z)\n"
			"\n"
			"- Set camera direction baed on a vector\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

