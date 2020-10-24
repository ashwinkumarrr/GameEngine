#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}
void MaterialLoader::LoadMaterial(std::string file_)
{
	std::ifstream in(file_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL " + file_, "LoadObjModel.cpp", __LINE__);
		return;
	}

	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
		}
		m.name = matName;
	}
	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);

	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}