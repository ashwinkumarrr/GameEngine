#include "LightSource.h"
LightSource::LightSource(glm::vec3 position_, float AmbientValue_, float DiffuseValue_, glm::vec3 lightColor_)
{
	position = position_;
	lightColor = lightColor_;
	AmbientValue = AmbientValue_;
	DiffuseValue = DiffuseValue_;
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}
void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}
glm::vec3 LightSource::GetLightColor()
{
	return lightColor;
}
void LightSource::SetLightColor(glm::vec3 lightColor_)
{
	lightColor = lightColor_;
}
float LightSource::GetAmbientValue()
{
	return AmbientValue;
}
void LightSource::SetAmbientValue(float AmbientValue_)
{
	AmbientValue = AmbientValue_;
}
float LightSource::GetDiffuseValue()
{
	return DiffuseValue;
}
void LightSource::SetDiffuseValue(float DiffuseValue_)
{
	DiffuseValue = DiffuseValue_;
}