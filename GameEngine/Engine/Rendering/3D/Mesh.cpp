#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_,  GLuint shaderProgram_) : VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0), textureLoc(0)
{
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}
Mesh::~Mesh(){
	OnDestroy();
}
void Mesh::OnDestroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}
	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}
void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPrespective()));

	glm::vec3 copyCamPos = camera_->GetPosition();
	glm::vec3 copyLightPos = camera_->GetLightSource()[0]->GetPosition();
	glm::vec3 copyLightColor = camera_->GetLightSource()[0]->GetLightColor();

	glUniform3f(lightPosLoc, copyLightPos.x, copyLightPos.y, copyLightPos.z);
	glUniform1f(lightAmbientLoc, camera_->GetLightSource()[0]->GetAmbientValue());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSource()[0]->GetDiffuseValue());
	glUniform3f(lightColorLoc, copyLightColor.x, copyLightColor.y, copyLightColor.z);


	glBindVertexArray(VAO);
	for(int i = 0; i<instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambientValue");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.color");
}