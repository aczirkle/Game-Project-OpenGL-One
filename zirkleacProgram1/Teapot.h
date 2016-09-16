#include "GlutObject.h"


class Teapot : public GlutObject
{
	public:
		//Teapot( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f), 
		//	   float innerRadius= 0.25f, float outerRadius = 1.0f, 
		//	   int sides = 8, int rings = 16);
		Teapot(glm::vec4 color = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f),double size=3);
		virtual void draw();
		//void makeTeapot();

	protected:
		
		GLdouble size;

};
