#include "Model.h"


Model::Model(const std::string& objFilePath_, const std::string& mtlFilePath_,GLuint shaderProgram_) : subMeshes(std::vector<Mesh*>()),	shaderProgram(0), modelInstance(std::vector<glm::mat4>())
{

	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
	modelInstance.reserve(5);

	obj = new LoadOBJModel();
	obj->LoadModel(objFilePath_, mtlFilePath_);
	this->LoadModel();
}
Model::~Model(){
	OnDestroy();
}
void Model::OnDestroy()
{
	if (subMeshes.size() > 0)
	{
		for (Mesh* m : subMeshes)
		{
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}
	modelInstance.clear();
}
void Model::Render(Camera* camera_)
{
	
	for (auto m : subMeshes)
	{
		m->Render(camera_, modelInstance);
	}
}
void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}
glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 roation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, roation_);
	model = glm::scale(model, scale_);
	return model;
}
glm::mat4 Model::GetTransform(int index_) const
{
	return modelInstance[index_];
}

BoundingBox Model::GetBoundingBox()
{
	return box;
}
int Model::CreateInstace(glm::vec3 position_, float angle_, glm::vec3 roation_, glm::vec3 scale_)
{
	modelInstance.push_back(GetTransform( position_, angle_, roation_, scale_));
	return modelInstance.size() - 1;

}
void Model::UpdateInstace(int index_, glm::vec3 position_, float angle_, glm::vec3 roation_, glm::vec3 scale_)
{
	modelInstance[index_] = GetTransform(position_, angle_, roation_, scale_);
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

void Model::LoadModel() 
{
	for (int i = 0; i < obj->GetSubMesh().size(); i++)
	{
		subMeshes.push_back(new Mesh(obj->GetSubMesh()[i], shaderProgram));
	}

	box = obj->GetBoundingBox();
	delete obj;
	obj = nullptr;
}