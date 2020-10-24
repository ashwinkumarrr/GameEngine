
#ifndef COMPONENTB_H 
#define COMPONENTB_H 

#include "../../Rendering/3D/GameObject.h"
#include "../../Rendering/3D/Component.h"


class ComponentB : public Component
{
public:

	ComponentB();
	~ComponentB();

	bool OnCreate(GameObject* parent_);
	void Update(float deltaTime_);

};
#endif