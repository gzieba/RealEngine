#include "ModelLoader.h"

#include "Model.h"
#include "Mesh.h"

#include "Common/logging.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelLoader::ModelLoader()
{

}

Model* ModelLoader::loadModel(std::string filePath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG(ERROR) << LOCATION << "ASSIMP::" << importer.GetErrorString();
		return nullptr;
	}

	LOG(INFO) << LOCATION << "Loading model: " << filePath;

	processNode(scene->mRootNode, scene);

	return new Model(m_meshes);
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

Mesh* ModelLoader::processMesh(aiMesh *mesh, const aiScene*)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

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

	// TODO: adding texture loading

	return new Mesh(std::move(vertices), std::move(indices));
}
