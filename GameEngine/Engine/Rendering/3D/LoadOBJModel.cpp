#include "LoadOBJModel.h"
LoadOBJModel::LoadOBJModel()
{
	currentMaterial = Material();
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}
LoadOBJModel::~LoadOBJModel()
{
	OnDestory();
}
void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& matlFilePath_)
{
	LoadMaterialLibrary(matlFilePath_);
	LoadModel(objFilePath_);
}
void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if(!in)
	{
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	box.maxVert = glm::vec3(FLT_MIN); 
	box.minVert = glm::vec3(FLT_MAX);
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			glm::vec3 vertex;
			float x, y, z;

			v >> x >> y >> z;
			
			vertex = glm::vec3(x, y, z);

			if (vertex.x < box.minVert.x){
				box.minVert.x = vertex.x;
			}
			if (vertex.y < box.minVert.y) {
				box.minVert.y = vertex.y;
			}
			if (vertex.z < box.minVert.z) {
				box.minVert.z = vertex.z;
			}

			if (vertex.x > box.maxVert.x) {
				box.maxVert.x = vertex.x;
			}
			if (vertex.y > box.maxVert.y) {
				box.maxVert.y = vertex.y;
			}
			if (vertex.z > box.maxVert.z) {
				box.maxVert.z = vertex.z;
			}

			vertices.push_back(glm::vec3(x, y, z));
		}
		if (line.substr(0, 3) == "vn ")
		{
			std::istringstream vn(line.substr(3));

			glm::vec3 norm;
			double x, y, z;

			vn >> x >> y >> z;

			norm = glm::vec3(x, y, z);
			normals.push_back(norm);
		}
		if (line.substr(0, 3) == "vt ")
		{
			std::istringstream vt(line.substr(3));
			glm::vec2 text;

			double x, y, z;

			vt >> x >> y >> z;

			text = glm::vec2(x, y);
			textureCoords.push_back(text);
		}
		if (line.substr(0, 2) == "f ")
		{
			std::istringstream f(line.substr(2));

			int x, y, z;
			char forwardslash;

			for (int i = 0; i < 3; i++) {

				f >> x >> forwardslash >> y >> forwardslash >> z;

				indices.push_back(x - 1);
				textureIndices.push_back(y - 1);
				normalIndices.push_back(z - 1);
			}
		}
		if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}

			LoadMaterials(line.substr(7));
		}
	}
	PostProcessing();
}
std::vector<Vertex> LoadOBJModel::GetVerts()
{
	return meshVertices;
}
std::vector<int> LoadOBJModel::GetIndices()
{
	return indices;
}
std::vector<SubMesh> LoadOBJModel::GetSubMesh()
{
	return subMeshes;
}
BoundingBox LoadOBJModel::GetBoundingBox()
{
	return box;
}

void LoadOBJModel::OnDestory()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}
void LoadOBJModel::PostProcessing()
{
	for (int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;

	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}
void LoadOBJModel::LoadMaterials(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}
void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}