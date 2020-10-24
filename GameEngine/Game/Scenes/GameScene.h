#ifndef GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Game/Scenes/Connection.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();



	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render();
};
#endif 