#include "GameScene.h"
#include "../../Engine/Core/TesterClass/ComponentA.h"
#include "../../Engine/Core/TesterClass/ComponentB.h"

GameScene::GameScene() : Scene()
{

}
GameScene::~GameScene()
{
	
}
bool GameScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);


	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLightSources(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 1.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* diceModel = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(0.0f, 0.0f, 0.0f)));
	
	Model* appleModel = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(appleModel);

    SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(6.0f, 0.0f, 0.0f)));

	GameObject* apple = new GameObject(appleModel);
	apple->SetScale(glm::vec3(0.5f));
	apple->AddComponent<ComponentA>();
	apple->AddComponent<ComponentB>();
	apple->GetComponent<ComponentA>();
	apple->RemoveComponent <ComponentA>();
	apple->RemoveComponent <ComponentB>();

	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	return true;
}
void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}
void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
void GameScene::OnDestroy()
{
	
}