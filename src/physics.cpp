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



class Cub {
public:
	glm::vec3 xC;
	glm::mat3 qC;// quaternions
	glm::vec3 CoM;

	glm::vec3 vel;

	float mass;

	glm::vec3 force;
	glm::vec3 pC, lC;

	glm::mat3 iBoxC;
	glm::mat3 iC;
	
	float torque;
	float wC;

private:
	

};	

Cub cub;

void PhysicsInit() {
	//

	randPos = glm::vec3(0.f, 0.f, 0.f);
	cub.xC = randPos;      
	cub.force = glm::vec3(0.f, -9.81f, 0.f);
	cub.pC = glm::vec3(0.f, 0.f, 0.f);
	cub.lC = glm::vec3(0.f, 0.f, 0.f);
	cub.iC = glm::mat3(1.0f);
	cub.iBoxC = glm::mat3(1.0f);
	cub.mass = 1;
	cub.vel = glm::vec3(0.f, 0.f, 0.f);
	cub.qC = glm::mat3(1.0f);
	cub.torque = 0.2f;
	cub.wC = 0.0f;
}
void PhysicsUpdate(float dt) {
	//TODO
	//ry = rand() % 3;
	//rz = rand()%3;
	//rx = rand() % 3;

	cub.lC = cub.lC + cub.torque * dt; //2.L

	cub.iBoxC = glm::mat3((1.f / 12.f) * cub.mass*(1 + 1)); 

	cub.iBoxC = glm::inverse(cub.iBoxC); 

	cub.iC = cub.qC * glm::inverse(cub.iBoxC) * glm::transpose(cub.qC); //5.I

	//cub.wC = cub.iC * cub.lC; //6.w 

	cub.pC = cub.pC + dt*cub.force; //1.I

	cub.vel = cub.pC / cub.mass;

	cub.xC = cub.xC + cub.vel * dt;


	randPos = glm::vec3(cub.xC.x, 5+ cub.xC.y, cub.xC.z);


}
void PhysicsCleanup() {
	//TODO
}

