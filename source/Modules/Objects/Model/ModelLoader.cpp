#include "ModelLoader.h"

#include "Model.h"
#include "Mesh.h"

#include "Common/logging.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::unique_ptr<Model> ModelLoader::loadModel(std::string filePath)
{
	m_directory = filePath.substr(0, filePath.find_last_of('/'));
	m_modelName = filePath.substr(filePath.find_last_of('/') + 1, filePath.back());
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG(ERROR) << LOCATION << "ASSIMP::" << importer.GetErrorString();
		return nullptr;
	}

	LOG(INFO) << LOCATION << "Loading model: " << filePath;

	processNode(scene->mRootNode, scene);

	return std::make_unique<Model>(Model(std::move(m_meshes)));
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene)
{
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

std::unique_ptr<Mesh> ModelLoader::processMesh(aiMesh *mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture2D> textures;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		if(mesh->mNormals)
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if(mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(vertex);
	}

	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		auto specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return std::make_unique<Mesh>(Mesh(vertices, indices, textures));
}

ModelLoader::Texture2D ModelLoader::createTexture2D(const char *fileName)
{
	int width, height, numberOfChannels = 0;
	unsigned char* data = stbi_load(fileName, &width, &height, &numberOfChannels, 0);
	if(!data)
	{
		LOG(ERROR) << LOCATION << "Could not load texture: " << fileName;
		return Texture2D();
	}

	return Texture2D(data, width, height, numberOfChannels);
}

std::vector<ModelLoader::Texture2D> ModelLoader::loadMaterialTextures(aiMaterial *material, aiTextureType type)
{
	std::vector<Texture2D> textures;

	for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString path;
		material->GetTexture(type, i, &path);
		auto filePath = m_directory + std::string("/") + path.C_Str();
		LOG(INFO) << LOCATION << "Loading texture: " << filePath;
		auto texture = createTexture2D(filePath.c_str());
		textures.push_back(texture);
	}
	return textures;
}
