#pragma once

#include <memory>
#include <map>

#include "Common/Components/Transform.h"
#include "Common/Components/Vertex.h"

#include "OpenGLCamera.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "OpenGLTexture2D.h"
#include "OpenGLLighting.h"

#include "Modules/Renderer/DirectionalLight.h"

class OpenGLRenderingObject
{
	typedef std::tuple<unsigned char*, int, int, int> Texture2D;
public:
	OpenGLRenderingObject(unsigned int id, Transform transform,
						  std::vector<Vertex> vertices,
						  std::vector<unsigned int> indices);

	unsigned int getID() const;
	unsigned int getIndicesCount() const;
	std::map<TextureType, OpenGLTexture2D>& getTextures();
	Transform getTransform() const;
	void setTransform(Transform transform);
	void setTexture(TextureType type, Texture2D data);
	const std::unique_ptr<OpenGLVertexArray>& getVAO() const;
	void setupShader(const OpenGLShader& shader, const OpenGLCamera& camera);
	void setupTextures(const OpenGLShader& shader);
	void setupLight(const OpenGLShader& shader, OpenGLLighting lighting);

private:
	void setupTransformation(const OpenGLCamera& camera);

	unsigned int m_id;
	unsigned int m_indicesCount;
	Transform m_transform;
	std::unique_ptr<OpenGLVertexArray> m_vao;
	std::map<TextureType, OpenGLTexture2D> m_textures =
	{
		{TextureType::albedo, {}},
		{TextureType::normal, {}},
		{TextureType::metallic, {}},
		{TextureType::roughness, {}},
		{TextureType::ao, {}}
	};

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
};

