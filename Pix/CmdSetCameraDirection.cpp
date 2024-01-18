#include "CmdSetCameraDirection.h"
#include "PixCamera.h"
#include "VariableCache.h"

bool CmdSetCameraDirection::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 3)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);

	Vector3 direction{ x,y,z };
	PixCamera::Get()->SetDirection(direction);
	return true;
}
