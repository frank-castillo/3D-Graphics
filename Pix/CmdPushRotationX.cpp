#include "CmdPushRotationX.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushRotationX::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const float radian = vc->GetFloat(params[0]) * X::Math::kDegToRad;

	MatrixStack::Get()->PushRotationX(radian);
	return true;
}
