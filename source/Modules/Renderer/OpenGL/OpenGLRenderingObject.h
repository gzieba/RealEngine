#pragma once

#include <memory>
#include <vector>

#include "Common/Components/Transform.h"
#include "Common/Components/Vertex.h"

#include "OpenGLCamera.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "OpenGLTexture2D.h"

class OpenGLRenderingObject
{
	typedef std::tuple<unsigned char*, int, int, int> Texture2D;
public:
	OpenGLRenderingObject(unsigned int id, Transform transform,
						  std::vector<Vertex> vertices,
						  std::vector<unsigned int> indices,
						  std::vector<Texture2D> textures);

	unsigned int getID() const;
	unsigned int getIndicesCount() const;
	Transform getTransform() const;
	void setTransform(Transform transform);
	const std::unique_ptr<OpenGLVertexArray>& getVAO() const;
	void setupShader(OpenGLShader shader, const OpenGLCamera& camera);
	void setupTextures(OpenGLShader shader);
	void setupLight(const OpenGLShader& shader);

private:
	void setupTransformation(const OpenGLCamera& camera);

	unsigned int m_id;
	unsigned int m_indicesCount;
	Transform m_transform;
	std::unique_ptr<OpenGLVertexArray> m_vao;
	std::vector<OpenGLTexture2D> m_textures;

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
};

