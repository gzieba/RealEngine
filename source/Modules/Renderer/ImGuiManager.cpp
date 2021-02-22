#include "ImGuiManager.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"

#include <GLFW/glfw3.h>

#include "Common/logging.h"

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
}

ImGuiManager::~ImGuiManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::newFrame(std::vector<OpenGLRenderingObject>& objects)
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		static int counter = 0;

		ImGui::Begin("RealEngine");                       // Create a window called "Hello, world!" and append into it.

		if(ImGui::Button("LoadModel"))
		{
			auto path = ImGuiFileDialog::Instance()->GetFilePathName();
			LOG(INFO) << LOCATION << path;
			sendMessage({MessageType::LoadModel, std::string("/home/gzieba/Developer/repos/build-RealEngine-Desktop_Qt_6_0_1_GCC_64bit-Debug/nanosuit/nanosuit.obj")});
		}

		if(ImGui::CollapsingHeader("Objects"))
		{
			if(ImGui::CollapsingHeader("Models"))
			{
				for(auto& object : m_objects)
				{
					if(ImGui::TreeNode(
								(std::get<1>(object)
								 + "(" + std::to_string(std::get<0>(object))
								 + ")").c_str()))
					{
						createMeshUi(object, objects);
					}
				}
			}
			if(ImGui::CollapsingHeader("Lights"))
			{
//				lightManager->CreateUi();
			}
		}
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
			m_objects.emplace_back(message.getData<std::tuple<int, std::string, Transform>>());
			break;
		}
		default:
			return;
	}
}

void ImGuiManager::createMeshUi(std::tuple<int, std::string, Transform>& object, std::vector<OpenGLRenderingObject>& objects)
{
	auto position = std::get<2>(object).getPosition();
	auto rotation = std::get<2>(object).getRotation();
	auto scale = std::get<2>(object).getScale();
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
	std::get<2>(object) = newTransform;
	for(auto& obj : objects)
	{
		if(obj.getID() == std::get<0>(object))
			obj.setTransform(newTransform);
	}

	ImGui::TreePop();
	ImGui::Separator();
}
