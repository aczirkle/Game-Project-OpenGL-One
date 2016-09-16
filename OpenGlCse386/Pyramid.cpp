#include "Pyramid.h"

Pyramid::Pyramid(GLfloat w , GLfloat h){
		height=h; 
		width=w;
}


void Pyramid::initialize(){

	glUseProgram(shaderProgram);
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xffffffff);

	GLuint VBO;
	GLuint CBO;
	GLuint IBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	glm::vec3 v0 = glm::vec3( -width/2.0f, -height/2.0f,width/2.0f);
	glm::vec3 v1 = glm::vec3( -width/2.0f, -height/2.0f, -width/2.0f);
	glm::vec3 v2 = glm::vec3( width/2.0f, -height/2.0f,width/2.0f);
	glm::vec3 v3 = glm::vec3( width/2.0f, -height/2.0f, -width/2.0f);

	glm::vec3 v4 = glm::vec3( 0.0f, height/2.0f, 0.0f);

	

	vector<glm::vec3> v;
	v.push_back( v0 );
	v.push_back( v1 );
	v.push_back( v2 );
	v.push_back( v3 );
	v.push_back( v4 );

	glGenBuffers(1, &VBO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO);
	glBufferData( GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec3), &v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	vector<glm::vec4> c;
	c.push_back( glm::vec4(-0.75f, 0.0f, 0.0f, 1.0f) );
	c.push_back( glm::vec4(-0.25f, 0.25f, 0.0f, 1.0f) );
	c.push_back( glm::vec4(0.0f, 0.75f, 0.0f, 1.0f) );

	c.push_back( glm::vec4(0.2f, 0.25f, 0.0f, 1.0f) );
	c.push_back( glm::vec4(0.2f, 0.45f, 0.0f, 1.0f) );



	glGenBuffers(1, &CBO);
	glBindBuffer( GL_ARRAY_BUFFER, CBO);
	glBufferData( GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec4), &c[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	vector<GLuint> indices;
	
	
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(4);

	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(1);

	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(2);
	
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);

	glGenBuffers(1, &IBO);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,
		indices.size( )* sizeof(GLuint),
		&indices[0],
		GL_STATIC_DRAW);
	numberOfIndices = indices.size();
VisualObject::initialize();


	cout << "pyramid initialize method called." << endl;
} 

void Pyramid::draw()
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));
	glBindVertexArray(vertexArrayObject);


	glDrawElements( GL_TRIANGLES, numberOfIndices, 	GL_UNSIGNED_INT, 0 );

	// Draw all children
	VisualObject::draw();

//	cout << "Pyramid draw method called." << endl;
}

