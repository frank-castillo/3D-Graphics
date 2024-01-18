#pragma once
#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(<Topology>, <3D>)\n"
			"\n"
			"- Begin primitive drawing.\n"
			"- Topology can be: point, line, or triangle\n"
			"- Optional: 3D can be true or false\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

