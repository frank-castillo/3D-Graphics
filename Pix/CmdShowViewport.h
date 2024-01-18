#pragma once
#include "Command.h"
class CmdShowViewport : public Command
{
public:
	const char* GetName() override
	{
		return "ShowViewport";
	}

	const char* GetDescription() override
	{
		return
			"SetViewport(<bool>)\n"
			"\n"
			"- Set viewport visibility\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

