#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	FillMode fillMode = FillMode::None;

	if (params[0] == "solid")
	{
		fillMode = FillMode::Solid;
	}
	else if (params[0] == "wireframe")
	{
		fillMode = FillMode::Wireframe;
	}

	Rasterizer::Get()->SetFillMode(fillMode);
	return true;
}