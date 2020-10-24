#include "Game1.h"

Game1::Game1() : GameInterFace(), currentSceneNum(0), currentScene(nullptr)
{

}
Game1::~Game1()
{
	OnDestroy();
}
void Game1::OnDestroy()
{
	delete currentScene;
	currentScene = nullptr;
}
bool Game1::OnCreate()
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate(); 
	}
	Debug::FatalError("Engine's scene is not initialized ", "Game1.cpp", __LINE__);
	return false;
}
void Game1::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}
void Game1::Render()
{
	currentScene->Render();
}
void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate())
	{
		CoreEngine::GetInstance()->Exit();
	}
}