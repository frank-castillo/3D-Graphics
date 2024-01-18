#include "CmdShowViewport.h"

#include "VariableCache.h"
#include "Viewport.h"

bool CmdShowViewport::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const bool isViewportActive = vc->GetBool(params[0]);

	Viewport::Get()->ShowViewport(isViewportActive);
	return true;
}
