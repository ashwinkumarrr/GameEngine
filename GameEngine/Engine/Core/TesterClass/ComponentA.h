
#ifndef COMPONENTA_H 
#define COMPONENTA_H 

#include "../../Rendering/3D/GameObject.h"
#include "../../Rendering/3D/Component.h"


class ComponentA : public Component
{
public:

	ComponentA();
	~ComponentA();


	bool OnCreate(GameObject* parent_);
	void Update(float deltaTime_);

};
#endif