#include "CmdSetCameraFarPlane.h"
#include "PixCamera.h"
#include "VariableCache.h"

bool CmdSetCameraFarPlane::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const float farPlane = vc->GetFloat(params[0]);

	PixCamera::Get()->SetFarPlane(farPlane);
	return true;
}
