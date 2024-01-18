//====================================================================================================
// Filename:	WinMain.h
// Created by:	Peter Chan
//====================================================================================================

#include "MathTest.h"
#include "PixEditor.h"

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ========== run Math Tests ========== //
	TestVector3();
	TestMatrix4();

	// ========== run Pix ========== //
	PixEditor editor;

	X::Start("xconfig.json");
	editor.Initialize();

	X::Run([&](float deltaTime)
	{
		return editor.Run(deltaTime);
	});

	editor.Terminate();
	X::Stop();
	return 0;
}