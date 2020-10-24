#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

struct Material {
	inline Material() :diffuseMap(0), shininess(0.0f), transparency(0.0f), ambient(glm::vec3(1.0f)),
		diffuse(glm::vec3(1.0f)), specular(glm::vec3()), name("") {
	}
	GLuint diffuseMap;

	float shininess;	
	float transparency;

	glm::vec3 ambient;
	glm::vec3 diffuse; 
	glm::vec3 specular; 

	std::string name;
};

class MaterialHandler
{
public:
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator=(MaterialHandler&&) = delete;

	static MaterialHandler* GetInstance();
	void AddMaterial(Material mat_);
	const Material GetMaterial(const std::string& matName_);

	void OnDestroy();
private:
	MaterialHandler();
	~MaterialHandler();

	static std::unique_ptr<MaterialHandler> materialInstance;
	friend std::default_delete<MaterialHandler>;

	static std::vector<Material> materials;
};
#endif 