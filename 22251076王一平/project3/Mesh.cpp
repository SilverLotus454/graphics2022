/*###################################################
##  �ļ�: Mesh.cpp
##  �ļ�˵���� ���ڵ���fbx��obj�����͵�ģ���ļ�
#####################################################*/
#include "Mesh.h"

// Ϊ��ǰMesh��vertices��indices��textures��ֵ���������Ͱ�VAO��VBO��EBO�ȣ�����ΪVAO��ֵ��
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, vector<glm::vec3> positions)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->positions = positions;
	setupMesh();
}

// ��Fragment Shader��uniform sampler��ֵ
void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); 
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); 
		else if (name == "texture_height")
			number = std::to_string(heightNr++); 

		// ��Fragment Shader��uniform sampler��ֵ
		glUniform1i(glGetUniformLocation(shader.programID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// GL_TRIANGLESΪͼԪ��indices.size()��ʾһ��ʵ����instance���������ٶ���
	// GL_UNSIGNED_INT��ʾ�����������������ͣ�0��ʾ��һ��������λ��
	// positions.size()��ʾҪ���ƶ��ٸ�ʵ��
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, positions.size());
	
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}


void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	// ���ò�ͬʵ����Instance��λ�õ�VBO
	glGenBuffersARB(1, &pVBO);
	glBindBufferARB(GL_ARRAY_BUFFER, pVBO);
	glBufferDataARB(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointerARB(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArrayARB(3);
	// ָ��layout(location = 3)�������ڻ��Ʋ�ͬʵ��ʱ�Ÿı�
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}

