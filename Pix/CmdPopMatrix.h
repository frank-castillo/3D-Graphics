#pragma once

#include "Command.h"

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}

	const char* GetDescription() override
	{
		return
			"PopMatrix(<void>)\n"
			"\n"
			"- Gets rid of the last computed matrix and reverts to the previous value\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

