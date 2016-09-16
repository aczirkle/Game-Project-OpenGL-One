#include "PointPoint.h"


// Constructor sets the position of the object,
// the axis about which it will rotate, and the rate and direction
// of rotation.
PointPoint::PointPoint( GLfloat pos,
							GLfloat h,
							 GLfloat d)
{
	position = pos;
	//axis= ax;
	distance=d;
	height=h;
	
	glm::translate(glm::mat4(1.0f), glm::vec3(pos, height, distance));
}


void PointPoint::update(float elapsedTimeSeconds)
{
	static float rot;
	rot+= elapsedTimeSeconds;
	float distance =+ elapsedTimeSeconds;
	float bounce = height*cos(rot);
		if(distance==12)
			target->~VisualObject();
		else
			target->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position, height, distance));


} // end update