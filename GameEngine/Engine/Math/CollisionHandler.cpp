#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevColliions =
std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler()
{
	prevColliions.reserve(10);
}
CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}
CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}
void CollisionHandler::OnCreate(float worldSize_)
{
	prevColliions.clear();
	scenePartition = new OctSpatialPartition(worldSize_);
}
void CollisionHandler::AddObject(GameObject* go_)
{
	scenePartition->AddObject(go_);
}
void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition_, CoreEngine::GetInstance()->GetWindowsize(), CoreEngine::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevColliions) {
			if (c != hitResult && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
			c = nullptr;
		}
		prevColliions.clear();

		if (hitResult) {
			prevColliions.push_back(hitResult);
		}
	}
}
void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	for (auto entry : prevColliions) {
		entry = nullptr;
	}
	prevColliions.clear();
}