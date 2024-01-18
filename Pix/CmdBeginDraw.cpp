#include "CmdBeginDraw.h"
#include "PrimitiveManager.h"

bool CmdBeginDraw::Execute(const std::vector<std::string>& params)
{
	// To execute we need to specify the topology
	if(params.size() != 2)
	{
		return false;
	}

	bool use3D = false;

	Topology topology = Topology::None;
	if (params[0] == "point")
	{
		topology = Topology::Point;
	}
	else if (params[0] == "line")
	{
		topology = Topology::Line;
	}
	else if (params[0] == "triangle")
	{
		topology = Topology::Triangle;
	}

	if (params[1] == "true" || params[1] == "1")
	{
		use3D = true;
	}
	else if (params[1] == "false" || params[1] == "0")
	{
		
		use3D = false;
	}

	PrimitiveManager::Get()->BeginDraw(topology, use3D);

	return true;
}
