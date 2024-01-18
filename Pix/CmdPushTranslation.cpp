#include "CmdPushTranslation.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushTranslation::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 3)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);;

	Vector3 translationVector { x,y,z };

	MatrixStack::Get()->PushTranslation(translationVector);
	return true;
}
