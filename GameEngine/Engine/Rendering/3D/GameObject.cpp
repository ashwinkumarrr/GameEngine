#include "GameObject.h"
#include "Component.h"



GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr)
{
	model = model_;
	position = position_;
	angle = 2.0f;
	rotation = glm::vec3(0.0f,4.0f,0.0f);
	scale = glm::vec3(2.0f);
	tag = "";
	hit = false;
	if (model)
	{
		modelInstance = model->CreateInstace(position, angle, rotation, scale);
		box = model->GetBoundingBox();
		box.transform = model->GetTransform(modelInstance);
	}
}
GameObject::~GameObject(){
	OnDestroy();
}
void GameObject::OnDestroy()
{
model = nullptr;
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;

}

std::string GameObject::GetTag() const
{
	return tag;
}

void GameObject::Render(Camera* camera_)
{
	if (model)
	{
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}
float GameObject::GetAngle() const
{
	return angle;
}
glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}
glm::vec3 GameObject::GetScale() const
{
	return scale;
}
BoundingBox GameObject::GetBoundingBox()
{
	return box;
}
bool GameObject::GetHit() const
{
	return hit;
}

void GameObject::SetPosition(glm::vec3 Position_)
{
	position = Position_;
	if (model)
	{
		model->UpdateInstace(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstace(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstace(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}

}
void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstace(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
		box.minVert *= scale.x > 2.0f ? 2.0f : (scale.x / 2.0f);
		box.maxVert *= scale.x > 2.0f ? 2.0f : (scale.x / 2.0f);
	}
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	hit = hit_;
	if (hit) {
		std::cout << tag << " Was Hit " << std::endl; 
	}
}
