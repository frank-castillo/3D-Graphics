#pragma once
#include "Command.h"
class CmdSetFillMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetFillMode";
	}

	const char* GetDescription() override
	{
		return
			"SetFillMode(<FillMode>)\n"
			"\n"
			"- Set triangle fill mode\n"
			"- Mode can be wireframe or solid\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

