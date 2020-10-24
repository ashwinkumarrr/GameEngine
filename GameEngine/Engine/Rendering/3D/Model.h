#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"


class Model
{
public: 
    Model(const std::string& objFilePath_, const std::string& mtlFilePath_, GLuint shaderProgram_);
   ~Model();
    void Render(Camera* camera_);
    void AddMesh(Mesh* mesh_);
    glm::mat4 GetTransform(int index_) const;
    BoundingBox GetBoundingBox();
    void OnDestroy();

    int CreateInstace(glm::vec3 position_, float angle_, glm::vec3 roation_, glm::vec3 scale_);
    void UpdateInstace(int index_,glm::vec3 position_, float angle_, glm::vec3 roation_, glm::vec3 scale_);
	GLuint GetShaderProgram() const;


private:
    std::vector <Mesh*> subMeshes;
    GLuint shaderProgram;
    BoundingBox box;
    std::vector<glm::mat4> modelInstance;

    glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 roation_, glm::vec3 scale_) const;
    void LoadModel();

    LoadOBJModel* obj;
};
#endif 