#include "Apps/DrawCubeApp.h"
#include "Apps/DrawMultipleObjectsApp.h"
#include "Apps/ClearColorApp.h"
#include "Apps/Texture2DApp.h"
#include <iostream>


int main(void)
{
	std::unique_ptr<ExperimentalApps::DrawCubeApp> app = std::make_unique<ExperimentalApps::DrawCubeApp>();
	//std::unique_ptr<test::TestClearColor> app = std::make_unique<test::TestClearColor>();
	//std::unique_ptr<test::TestDrawMultipleObjects> app = std::make_unique<test::TestDrawMultipleObjects>();
	//std::unique_ptr<test::TestTexture2D> app = std::make_unique<test::TestTexture2D>();
	app->Run();
	

	return 0;
}

