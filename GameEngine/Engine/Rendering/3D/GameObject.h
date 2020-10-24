#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H 

#include "Model.h"
#include "Component.h"

using namespace glm;
using namespace std;


class Component;
class GameObject
{
public:

	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();

	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox();
	std::string GetTag() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 Position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void OnDestroy();
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);


	template<typename T, typename ... Template>
	void AddComponent(Template&& ... template_)
	{
		T* D = new T(std::forward<Template>(template_)...);

		if (dynamic_cast<Component*>(D))
		{
			if (!GetComponent<T>())
			{
				componentContainer.push_back(D);
				D->OnCreate(this);
			}
			else
			{
				cout << " Component " << endl;
				delete D;
				D = nullptr;
				return;
			}
		}
		else
		{
			cout << " Template " << endl;
			delete D;
			D = nullptr;
		}
	}

	template<typename T>
	T* GetComponent()
	{
		if (componentContainer.size() != 0)
		{
			for (auto i = 0; i < componentContainer.size(); i++)
			{
				if (T* G = dynamic_cast<T*>(componentContainer[i]))
				{
					return G;
				}
			}
		}

		return nullptr;
	}

	template<typename T>
	void RemoveComponent()
	{
		for (size_t i = 0; i < componentContainer.size(); i++)
		{
			if (T* d = dynamic_cast<T*>(componentContainer[i]))
			{
				delete componentContainer[i];
				componentContainer[i] = nullptr;
				componentContainer.erase(componentContainer.begin() + i);
				break;
			}
		}
	}

private:
	Model* model;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	int modelInstance;

	std::vector<Component*> componentContainer;

	BoundingBox box;
	std::string tag;

	bool hit;
};
#endif