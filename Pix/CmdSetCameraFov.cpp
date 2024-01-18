#include "CmdSetCameraFov.h"
#include "PixCamera.h"
#include "VariableCache.h"

bool CmdSetCameraFov::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const float fov = vc->GetFloat(params[0]);

	PixCamera::Get()->SetFOV(fov);
	return true;
}