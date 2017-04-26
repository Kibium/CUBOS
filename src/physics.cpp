#include <glm\gtc\matrix_transform.hpp>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\mat4x4.hpp>
bool show_test_window = false;
namespace Cube {

	extern void updateCube(const glm::mat4& transform);

}
void GUI() {
	{	//FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//TODO
	}
	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

extern glm::vec3 randPos;
extern float x, y, z,rx,ry,rz;

glm::mat4 position(1.f);
glm::vec3 force;
glm::vec3 rotation;
void PhysicsInit() {
	//
	x = 0;
	z = 0;
	y = 5;
	//randPos = glm::vec3(x, y, z);
	//glm::translate(position, randPos);
	

}
void PhysicsUpdate(float dt) {
	//TODO
	ry = rand() % 3;
	rz = rand()%3;
	rx = rand() % 3;



	Cube::updateCube(position);
}
void PhysicsCleanup() {
	//TODO
}

