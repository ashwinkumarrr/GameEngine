#ifndef  LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include<glm/glm.hpp>
class LightSource
{
public:
	LightSource(glm::vec3 position_, float AmbientValue_, float DiffuseValue_, glm::vec3 lightColor_);
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position_);
	glm::vec3 GetLightColor();
	void SetLightColor(glm::vec3 lightColor_);
	float GetAmbientValue();
	void SetAmbientValue(float AmbientValue_);
	float GetDiffuseValue();
	void SetDiffuseValue(float DiffuseValue_);

private:
	glm::vec3 position;
	glm::vec3 lightColor;
	float AmbientValue;
	float DiffuseValue;
};
#endif