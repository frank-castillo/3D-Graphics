#include "CmdVertex.h"

#include "PrimitiveManager.h"
#include "VariableCache.h"
#include "Vertex.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 2 || params.size() > 6)
	{
		return false;
	}

	Vertex vertex;

	auto vc = VariableCache::Get();

	if (params.size() == 2)
	{
		vertex.pos.x = vc->GetFloat(params[0]);
		vertex.pos.y = vc->GetFloat(params[1]);
		vertex.color = X::Colors::White;
	}
	else if (params.size() == 5)
	{
		vertex.pos.x = vc->GetFloat(params[0]);
		vertex.pos.y = vc->GetFloat(params[1]);
		vertex.color.r = vc->GetFloat(params[2]);
		vertex.color.g = vc->GetFloat(params[3]);
		vertex.color.b = vc->GetFloat(params[4]);
		vertex.color.a = 1.0f;
	}
	else if (params.size() == 6)
	{
		vertex.pos.x = vc->GetFloat(params[0]);
		vertex.pos.y = vc->GetFloat(params[1]);
		vertex.pos.z = vc->GetFloat(params[2]);
		vertex.color.r = vc->GetFloat(params[3]);
		vertex.color.g = vc->GetFloat(params[4]);
		vertex.color.b = vc->GetFloat(params[5]);
		vertex.color.a = 1.0f;
	}
	else
	{
		return false;
	}

	PrimitiveManager::Get()->AddVertex(vertex);
	return true;
}
