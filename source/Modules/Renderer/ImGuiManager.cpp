#include "ImGuiManager.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"

#include <GLFW/glfw3.h>

#include "Common/logging.h"
#include "Modules/Objects/Model/ModelLoader.h"

namespace
{
constexpr auto GLSL_VERSION = "#version 410";
}

ImGuiManager::ImGuiManager(GLFWwindow* window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiFileDialog::Instance()->SetExtentionInfos(".obj", ImVec4(1.0f, 1.0f, 0.0f, 0.9f));
}

ImGuiManager::~ImGuiManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::loadModel()
{
	if(ImGui::Button("LoadModel"))
	{
		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileModel", "Choose File", ".obj,.fbx", ".");
	}

	if(ImGuiFileDialog::Instance()->Display("ChooseFileModel"))
	{
		if(ImGuiFileDialog::Instance()->IsOk())
		{
			auto path = ImGuiFileDialog::Instance()->GetFilePathName();
			LOG(INFO) << LOCATION << path;
			sendMessage({MessageType::LoadModel, std::string(path)});
		}

		ImGuiFileDialog::Instance()->Close();
	}
}

void ImGuiManager::loadTexture(OpenGLRenderingObject &object)
{
	typedef std::tuple<unsigned char*, int, int, int> Texture2D;
	if(ImGui::Button("LoadTexture"))
	{
		ImGuiFileDialog::Instance()->OpenDialog("ChooseTextureFile", "Choose File", ".jpg", ".");
	}
	if(ImGuiFileDialog::Instance()->Display("ChooseTextureFile"))
	{
		if(ImGuiFileDialog::Instance()->IsOk())
		{
			auto path = ImGuiFileDialog::Instance()->GetFilePathName();
			LOG(INFO) << LOCATION << path;
			auto texture = ModelLoader::createTexture2D(TextureType::albedo, path.c_str());
			object.setTexture(texture.first, texture.second);
		}
		ImGuiFileDialog::Instance()->Close();
	}
}

void ImGuiManager::newFrame(std::vector<OpenGLRenderingObject>& objects)
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		ImGui::Begin("RealEngine");                       // Create a window called "Hello, world!" and append into it.

		loadModel();

		if(ImGui::CollapsingHeader("Objects"))
		{
			if(ImGui::CollapsingHeader("Models"))
			{
				for(auto& object : objects)
				{
					if(ImGui::TreeNode(std::to_string(object.getID()).c_str()))
					{
						createMeshUi(object);
					}
				}
			}
			if(ImGui::CollapsingHeader("Lights"))
			{
//				lightManager->CreateUi();
			}
		}

        selectShader();

		ImGui::End();
	}


	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::handleMessage(const Message &message)
{
	switch (message.getMessageType())
	{
		case MessageType::ObjectListChanged:
		{
//			m_objects.emplace_back(message.getData<std::tuple<int, std::string, Transform>>());
			break;
		}
		default:
			return;
	}
}

void ImGuiManager::createMeshUi(OpenGLRenderingObject &object)
{
	auto position = object.getTransform().getPosition();
	auto rotation = object.getTransform().getRotation();
	auto scale = object.getTransform().getScale();
	float positionArr[] = {position.x, position.y, position.z};
	float rotationArr[] = {rotation.x, rotation.y, rotation.z};
	float scaleArr[] = {scale.x, scale.y, scale.z};

	ImGui::Text("Set model transformation.");

	ImGui::InputFloat3("Position", positionArr);
	ImGui::InputFloat3("Rotation", rotationArr);
	ImGui::InputFloat3("Scale", scaleArr);

	position.x = positionArr[0];
	position.y = positionArr[1];
	position.z = positionArr[2];

	rotation.x = rotationArr[0];
	rotation.y = rotationArr[1];
	rotation.z = rotationArr[2];

	scale.x = scaleArr[0];
	scale.y = scaleArr[1];
	scale.z = scaleArr[2];

	auto newTransform = Transform{position, rotation, scale};

	object.setTransform(newTransform);

	loadTexture(object);

	ImGui::TreePop();
    ImGui::Separator();
}

void ImGuiManager::selectShader()
{
    int newShader = m_currentSelectedShader;
    ImGui::RadioButton("Default shader", &newShader, 0); ImGui::SameLine();
    ImGui::RadioButton("Debug normal shader", &newShader, 1); ImGui::SameLine();
    ImGui::RadioButton("Debug tex shader", &newShader, 2);
    if(newShader != m_currentSelectedShader)
    {
        switch (newShader)
        {
            case 0:
            {
                sendMessage({MessageType::SetDefaultShader});
                break;
            }
            case 1:
            {
                sendMessage({MessageType::SetDebugNormalShader});
                break;
            }
            case 2:
            {
                sendMessage({MessageType::SetDebugTexCoordShader});
                break;
            }
        }
        m_currentSelectedShader = newShader;
        return;
    }
}
