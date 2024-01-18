#include "CmdSetCullMode.h"
#include "PrimitiveManager.h"
#include "VariableCache.h"

bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	CullMode cullMode = CullMode::None;

	if (params[0] == "None" || params[0] == "none")
	{
		cullMode = CullMode::None;
	}
	else if (params[0] == "Front" || params[0] == "front")
	{
		cullMode = CullMode::Front;
	}
	else if (params[0] == "Back" || params[0] == "back")
	{
		cullMode = CullMode::Back;
	}

	PrimitiveManager::Get()->SetCullMode(cullMode);

	return true;
}