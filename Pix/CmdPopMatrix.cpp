#include "CmdPopMatrix.h"
#include "MatrixStack.h"

bool CmdPopMatrix::Execute(const std::vector<std::string>& params)
{
	if (params.size() > 0)
	{
		return false;
	}

	MatrixStack::Get()->PopMatrix();
	return true;
}
