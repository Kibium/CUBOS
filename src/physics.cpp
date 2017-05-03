#include <glm\gtc\matrix_transform.hpp>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\mat4x4.hpp>
#include <glm\gtc\quaternion.hpp>

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
extern glm::mat4 qMat4; //Quaternion to matrix4


class Cub {
public:
	glm::vec3 xC; //Posición
	glm::quat qC; //Quaternions, orientation. X, Y, Z, W (W ~= Angulo de rotacion)
	glm::mat3 rC; //Quaternion to matrix3 = Orientation

	glm::vec3 vel; //Velocidad

	float mass; //Masa

	glm::vec3 force; //Fuerza
	glm::vec3 pC; //Lineal Momentum
	glm::vec3 lC; //Angular Momentum

	glm::mat3 iBodyC; //Inertia Tensor Body
	glm::mat3 iC; //Intertia Tensor
	
	float torque; //Torque
	glm::vec3 wC; //Velocidad Angular
	float wQuat;


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
	cub.iBodyC = glm::mat3(1.0f);
	cub.mass = 1;
	cub.vel = glm::vec3(0.f, 0.f, 0.f);
	 
	cub.torque = 0.0f;
	cub.wC = glm::vec3(0.0f);
}

void PhysicsUpdate(float dt) {
	//TODO
	//ry = rand() % 3;
	//rz = rand()%3;
	//rx = rand() % 3;

	//Translacion
	cub.pC = cub.pC + dt*cub.force;
	cub.vel = cub.pC / cub.mass;
	cub.xC = cub.xC + dt * cub.vel;

	//Rotacion
	cub.lC = cub.lC + cub.torque * dt;

	cub.rC = glm::mat3_cast(cub.qC);
	cub.iC = cub.rC * cub.iBodyC * glm::transpose(cub.rC);
	cub.wC = cub.iC * cub.lC;
	cub.qC = cub.qC + dt * 1/2 * glm::quat(0.f, 0.f,0.f, cub.wQuat) * cub.qC;
	cub.qC = normalize(cub.qC);
	qMat4 = mat4_cast(cub.qC);
	

	/*
	

	cub.iBodyC = glm::mat3((1.f / 12.f) * cub.mass*(1 + 1)); 

	cub.iBodyC = glm::inverse(cub.iBodyC); 

	cub.iC = cub.qC * (cub.iBodyC) * glm::transpose(cub.qC); 

	

	

	//cub.wC = cub.iC * cub.lC; //6.w 


	cub.xC = cub.xC + cub.vel * dt;


	randPos = glm::vec3(cub.xC.x, 5+ cub.xC.y, cub.xC.z);
	*/

}
void PhysicsCleanup() {
	//TODO
}

