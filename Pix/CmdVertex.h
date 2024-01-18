#pragma once
#include "Command.h"

class CmdVertex : public Command
{
public:
	const char* GetName() override
	{
		return "Vertex";
	}

	const char* GetDescription() override
	{
		return
			"Vertex(x, y)\n"
			"Vertex(x, y, r, g, b)\n"
			"\n"
			"- Adds a single vertex.\n"
			"- If no color is specified, will default to white\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

