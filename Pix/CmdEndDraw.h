#pragma once
#include "Command.h"

class CmdEndDraw : public Command
{
public:
	const char* GetName() override
	{
		return "EndDraw";
	}

	const char* GetDescription() override
	{
		return
			"EndDraw()\n"
			"\n"
			"- End primitive drawing\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

