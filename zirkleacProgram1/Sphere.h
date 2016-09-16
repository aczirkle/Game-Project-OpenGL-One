
#include "GlutObject.h"


class Sphere : public GlutObject
{
	public:
		//Sphere( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f), 
		//	   float innerRadius= 0.25f, float outerRadius = 1.0f, 
		//	   int sides = 8, int rings = 16);
		Sphere(glm::vec4 color = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f),float radius = 1.f, int slices = 16, int stacks=16);
		virtual void draw();
		//void makeTeapot();

	protected:
		
		GLdouble dInnerRadius;
		GLint slices, stacks;
};
