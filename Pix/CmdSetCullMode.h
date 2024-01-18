#pragma once

#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}

	const char* GetDescription() override
	{
		return
			"SetCullMode(<Cullmode>)\n"
			"\n"
			"- Cullmode can be: None, Front, or Back\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

