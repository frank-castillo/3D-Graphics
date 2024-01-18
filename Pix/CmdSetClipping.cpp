#include "CmdSetClipping.h"

#include "VariableCache.h"
#include "Clipper.h"

bool CmdSetClipping::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const bool isClippingActive = vc->GetBool(params[0]);

	Clipper::Get()->SetClipping(isClippingActive);
	return true;
}
