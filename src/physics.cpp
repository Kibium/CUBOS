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
glm::mat4 transform; // Matriu els canvis 


class Cubo {
public:

	glm::vec3 xC; // position
	glm::vec3 lastxC; //lastP
	glm::mat4 qC; // quaternions - orientation
	glm::vec3 pC; // Lineal momentum
	glm::vec3 lC; // Angular momentum

};
Cubo cub;
void PhysicsInit() {

	//Init

	
	x = 0;
	z = 0;
	y = 5;

	cub.xC = glm::vec3(x, y, z);
	cub.qC = glm::mat4(1.0f);
	cub.pC = glm::vec3(0.f, 0.f, 0.f);
	cub.lC = glm::vec3(0.f, 0.f, 0.f);

	

}
void PhysicsUpdate(float dt) {
	//TODO
	//ry = rand() % 1; // loco
	//rz = rand() % 2;
	//rx = rand() % 1;

	


	Cube::updateCube(transform);
}
void PhysicsCleanup() {
	//TODO
}

