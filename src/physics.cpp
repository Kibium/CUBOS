#include <glm\gtc\matrix_transform.hpp>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\mat4x4.hpp>
#include <glm\gtc\quaternion.hpp>
#include <iostream>
#include "glm/ext.hpp"
#include <time.h>
#include <ctime>
#include <vector>
#include <../include/GLFW/glfw3.h>
using namespace std;
bool show_test_window = false;
bool reset = false;
void Reset();
void PhysicsInit();
int Rtime;
time_t theTime = time(0);
void Reset() {
	PhysicsInit(); 
	
}
void timeReset() {
	theTime++;
	if (theTime > 1150) {
		PhysicsInit();
		theTime = 0;
	}
}
void GUI() {
	{    //FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//TODO
	}
	if (ImGui::Button("RESET")) {
		Reset();
	}
	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

float halfW = 0.5;
extern glm::vec3 randPos;
extern glm::mat4 qMat4;
bool collisioned, collisionDown, collisionUp, collisionLeft, collisionRight, collisionFront, collisionBack = false;
glm::mat4 *externRV, *lastExternRV;
glm::vec3 *vertexPosition, *LastVertex;
bool hasCollision(glm::vec3 preVertexPos, glm::vec3 n, float d, glm::vec3 vertexPos) {
	float getPos;
	getPos = ((glm::dot(n, preVertexPos) + d) * (glm::dot(n, vertexPos) + d));
	if (getPos <= 0) { return true; }
	else { return false; }
}
class Cub {
private:
public:
	glm::vec3 xC; //Posici�n
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
	glm::vec3 impulse;
	glm::vec3 torqueImpulse;
	glm::vec3 verts[8] = {		//vertices del cubo.
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
Cub *cub;
void PhysicsInit() {
	cub = new Cub;
	vertexPosition = new glm::vec3[8];
	LastVertex = new glm::vec3[8];
	externRV = new glm::mat4;
	lastExternRV = new glm::mat4;
	glm::vec3 random =glm::vec3(-4 +rand() % 10, -3+rand() % 10, -4+ rand() % 10);
	Rtime = 0;
	randPos = glm::vec3(random);
	cub->xC =  randPos;
	cub->force = glm::vec3(0.f, 0, 0.f);
	cub->pC = glm::vec3(0.f, 0.f, 0.f);
	cub->iC = glm::mat3(1.0f);
	cub->iBodyC = glm::mat3(1.0f);
	cub->vel = glm::vec3(0.f, 0.f, 0.f);
	cub->rC = glm::mat3(0.f);
	cub->torque = 1.f;
	cub->lC = cub->lC + cub->torque;
	cub->wC = glm::vec3(0.f);
	cub->qC = glm::quat(0.f, 0.f, 0.f, 0.f);
	cub->mass = 1.0f;
	cub->impulse = glm::vec3(0.f);
	cub->torqueImpulse = glm::vec3(0.f);
}

void detectLastPoint(glm::vec3 vertex, int i) {
	glm::vec4 v(vertex, 1);
	vertexPosition[i] = *externRV * v;
	LastVertex[i] = *lastExternRV * v;
}
void PhysicsCleanup() {
	delete externRV;
	delete lastExternRV;
	delete[] vertexPosition;
	delete[] LastVertex;
	delete cub;
}
void PhysicsUpdate(float dt) {
	theTime++;
	if (Rtime>100) {
		Reset();
	}
	for (int i = 0; i < 8; i++) {
		detectLastPoint(cub->verts[i], i);
		collisionDown = hasCollision(LastVertex[i], glm::vec3(0, 1, 0), 0, vertexPosition[i]);
		collisionUp = hasCollision(LastVertex[i], glm::vec3(0, -1, 0), 10, vertexPosition[i]);
		collisionLeft = hasCollision(LastVertex[i], glm::vec3(1, 0, 0), 5, vertexPosition[i]);
		collisionRight = hasCollision(LastVertex[i], glm::vec3(-1, 0, 0), 5, vertexPosition[i]);
		collisionFront = hasCollision(LastVertex[i], glm::vec3(0, 0, -1), 5, vertexPosition[i]);
		collisionBack = hasCollision(LastVertex[i], glm::vec3(0, 0, 1), 5, vertexPosition[i]);
	}	
	cub->force = glm::vec3(0, -9.81, 0);
	cub->pC = cub->pC + dt*cub->force;
	cub->vel = cub->pC / cub->mass;
	cub->xC = cub->xC + dt * cub->vel;
	
	cub->iBodyC = glm::mat3((1.f / 12.f) * cub->mass*(1 + 1));
	cub->iBodyC = glm::inverse(cub->iBodyC);
	cub->rC = glm::mat3_cast(cub->qC);
	cub->iC = cub->rC * cub->iBodyC * glm::transpose(cub->rC);
	cub->wC = cub->iC * cub->lC;
	cub->qC = cub->qC + dt *1.f / 2.f * glm::quat(0.f, cub->wC)  * cub->qC;
	cub->qC = normalize(cub->qC);
	qMat4 = mat4_cast(cub->qC);
	randPos = glm::vec3(cub->xC.x, cub->xC.y, cub->xC.z);
	for (int i = 0; i < 8; i++) {
		Rtime = glfwGetTime();
		if (collisionDown) {
			cub->impulse = cub->force;
			cub->pC = abs(cub->impulse);
			cub->vel = cub->impulse / cub->mass;
			for (int i = 0; i<8; i++)
				cub->torqueImpulse = cross((vertexPosition[i] - cub->xC), cub->impulse);
			cub->lC = cub->torqueImpulse;
			cub->wC = glm::inverse(cub->iC)*cub->torqueImpulse;
		}
		if (collisionUp) {}
		if (collisionLeft){}
		if (collisionRight){}
		if (collisionFront){}
		if (collisionBack){}
	}
	timeReset();
}

