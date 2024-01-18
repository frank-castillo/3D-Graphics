#include "CmdEndDraw.h"
#include "PrimitiveManager.h"

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
	if (params.size() > 0)
	{
		return false;
	}

	PrimitiveManager::Get()->EndDraw();
	return true;
}
