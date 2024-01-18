#include "CmdEnableDepth.h"
#include "VariableCache.h"
#include "DepthBuffer.h"

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const bool isActive = vc->GetBool(params[0]);

	DepthBuffer::Get()->SetEnabled(isActive);
	return true;
}
