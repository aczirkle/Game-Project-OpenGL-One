#include "Controller.h"
#include "glutbase.h"

class PointPoint : public Controller
{
	protected:
// Position at which the object is spinning in place
GLfloat position;
// axis of rotation
//glm::vec3 axis;
// rate and direction of rotation
GLfloat distance;
GLfloat height;

public:
// Constructor sets the position of the object,
// the axis about which it will rotate, and the rate and direction
// of rotation.
PointPoint( GLfloat pos = 0.f,
							GLfloat h = 2.5f,
							 GLfloat d = 3.5f);
void update(float elapsedTimeSeconds);
};