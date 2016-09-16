#pragma once
#include "Controller.h"
#include "OpenGLApplicationBase.h"
class PhysicsController :
	public Controller
{
public:
	PhysicsController(void);
	PhysicsController(float grav);
	PhysicsController(glm::vec3 pos, glm::vec3 vec, glm::vec3 acc);
	void launch(glm::vec3 start, glm::vec3 direction, float speed);
	void update(float elapsedTimeSeconds);
protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	GLfloat gravity;
};

