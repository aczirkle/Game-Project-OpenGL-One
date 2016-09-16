#include "Teapot.h"


#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

Teapot::Teapot( glm::vec4 color,double siz ):GlutObject(color)
{
	size=siz;

}

// Preform drawing operations
void Teapot::draw()
{
	GlutObject::draw();
	glutSolidTeapot(size);

} // end draw
