#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Graphics/TextureHandler.h"
#include <sstream>
#include "../../Math/BoundingBox.h"
#include "../../FX/MaterialLoader.h"

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objFilePath_, const std::string& matlFilePath_);
	void LoadModel(const std::string& filePath_);
	std::vector<Vertex> GetVerts();
	std::vector<int> GetIndices();
	std::vector<SubMesh> GetSubMesh();
	BoundingBox GetBoundingBox();
	void OnDestory();
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<int> indices, normalIndices, textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMeshes;

	void PostProcessing();
	void LoadMaterials(const std::string& matName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	Material currentMaterial;

	BoundingBox box;
};
#endif