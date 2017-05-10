
#include <glm\gtc\matrix_transform.hpp>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\mat4x4.hpp>
#include <glm\gtc\quaternion.hpp>
#include <iostream>
#include "glm/ext.hpp"
using namespace std;
bool show_test_window = false;
float halfW = 0.5;
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
glm::mat4 position(1.f);
extern glm::mat4 qMat4; //Quaternion to matrix4

						//posiciones de cada punto a partir del centro de masas.
glm::mat4 externRV(1.0);
bool hasCollision(glm::vec3 Pt, glm::vec3 n, float d, glm::vec3 PtPost, int plane) {

	float getPos;
	getPos = ((glm::dot(n, Pt) + d) * (glm::dot(n, PtPost) + d));
	if (getPos <= 0) { return true; }
	else { return false; }
}
class Cub {
private:

public:


	glm::vec3 xC; //Posición
	glm::vec3 force; //Fuerza
	glm::vec3 pC; //Lineal Momentum
	glm::vec3 lC; //Angular Momentum
	glm::mat3 iC; //Intertia Tensor
	glm::mat3 iBodyC; //Inertia Tensor Body
	glm::vec3 vel; //Velocidad
	glm::mat3 rC; //Quaternion to matrix3 = Orientation
	float torque; //Torque
	glm::vec3 wC; //Velocidad Angular
	glm::quat qC; //Quaternions, orientation. X, Y, Z, W (W ~= Angulo de rotacion)
	float mass; //Masa
				//vertices del cubo.
	glm::vec3 verts[8] = {
		glm::vec3(-halfW, -halfW, -halfW), //1
		glm::vec3(-halfW, -halfW,  halfW), //2
		glm::vec3(halfW, -halfW,  halfW),  //3
		glm::vec3(halfW, -halfW, -halfW),  //4
		glm::vec3(-halfW,  halfW, -halfW), //5
		glm::vec3(-halfW,  halfW,  halfW), //6
		glm::vec3(halfW,  halfW,  halfW),  //7
		glm::vec3(halfW,  halfW, -halfW)   //8
	};


};

Cub cub;

void PhysicsInit() {

	randPos = glm::vec3(0.f, 5.f, 0.f);
	cub.xC = randPos;
	cub.force = glm::vec3(0.f, -9.81f, 0.f);
	cub.pC = glm::vec3(0.f, 0.f, 0.f);
	cub.lC = glm::vec3(0.f, 0.f, 0.f);
	cub.iC = glm::mat3(1.0f);
	cub.iBodyC = glm::mat3(1.0f);
	cub.vel = glm::vec3(0.f, 0.f, 0.f);
	cub.rC = glm::mat3(0.f);
	cub.torque = 0.2f;
	cub.wC = glm::vec3(0.f);
	cub.qC = glm::quat(0.f, 0.f, 0.f, 0.f);
	cub.mass = 1.0f;
	qMat4 = glm::mat4(1.f);

}
bool collisioned;
void PhysicsUpdate(float dt) {

	//Euler
	//Translacion

	cub.pC = cub.pC + dt*cub.force;
	cub.vel = cub.pC / cub.mass;
	cub.xC = cub.xC + dt * cub.vel;
	//Rotacion
	cub.lC = cub.lC + cub.torque * dt;
	cub.iBodyC = glm::mat3((1.f / 12.f) * cub.mass*(1 + 1));
	cub.iBodyC = glm::inverse(cub.iBodyC);
	cub.rC = glm::mat3_cast(cub.qC);
	cub.iC = cub.rC * cub.iBodyC * glm::transpose(cub.rC);
	cub.wC = cub.iC * cub.lC;
	cub.qC = cub.qC + dt *1.f / 2.f * glm::quat(0.f, cub.wC)  * cub.qC;
	cub.qC = normalize(cub.qC);
	qMat4 = mat4_cast(cub.qC);
	randPos = glm::vec3(cub.xC.x, cub.xC.y, cub.xC.z);

	//posiciones de los vertices en nuestro mundo.
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 vertexPosition = externRV*glm::vec4(cub.verts[i], 1);
		


		//cout << glm::to_string(vertexPosition);
	}


}


void PhysicsCleanup() {
	//TODO
}






