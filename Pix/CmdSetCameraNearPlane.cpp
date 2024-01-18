#include "CmdSetCameraNearPlane.h"
#include "PixCamera.h"
#include "VariableCache.h"

bool CmdSetCameraNearPlane::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const float nearPlane = vc->GetFloat(params[0]);

	PixCamera::Get()->SetNearPlane(nearPlane);
	return true;
}
