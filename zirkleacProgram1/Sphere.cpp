#include "Sphere.h"


#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

Sphere::Sphere( glm::vec4 color, float innerRadius, int slic,  int stac):GlutObject(color)
{
	dInnerRadius =  innerRadius;
	slices=slic;
	stacks=stac;

}

// Preform drawing operations
void Sphere::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidSphere( dInnerRadius, slices, stacks);

} // end draw
