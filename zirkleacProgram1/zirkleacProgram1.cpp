#include "OpenGLApplicationBase.h"
#include "glutbase.h"

#include "Pyramid.h"
#include "Floor.h"
#include "Controller.h"
#include "SpinnerController.h"
#include "PointPoint.h"
#include "Torus.h"
#include "Sphere.h"
#include "Teapot.h"
#include "PhysicsController.h"

class zirkleacProgram1 : public OpenGLApplicationBase
{
	//friend void figureMenu(int value);
	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);
	friend void KeyboarCB(unsigned char Key, int x, int y);
protected: 
	Floor* floor;
	VisualObject* userplace;
	GLint view;
	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;
	GLuint shaderGLUT;
	int lives, score;
	bool running, user;

public:
	zirkleacProgram1 ()
		//:figure(1)
	{
		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" },
			{ GL_FRAGMENT_SHADER, "pcFS.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};

		ShaderInfo shadersGLUT[] = {
			{ GL_VERTEX_SHADER, "glutObjectUniViewProj.vert" },
			{ GL_FRAGMENT_SHADER, "glutObjectSolidColor.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		shaderGLUT = BuildShaderProgram(shadersGLUT);
		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		view=0;
		posX=0.f;
		posY=0.f;
		posZ=-25.0f;
		lives=3;
		score = 0;
		user=false;
		floor = new Floor(50);
		floor->setShader(shaderProgram);
		addChild(floor);

		glutSpecialFunc( SpecialKeyboardCB);

	}

	virtual void initialize()
	{
		glClearColor(.4f, 1.0f, .6f, .4f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		userPlace();
		VisualObject::initialize();
		 
	} // end initialize
	// Render scene objects
	virtual void draw()
	{ VisualObject::draw();
	if(user)
		userplace->draw();
	} // end draw

	// Update scene objects inbetween frames
	virtual void update( float elapsedTimeSec )
	{ 
		static int counter;
		setViewPoint();
		
		if(counter!=50 && running){
			counter++;
		checkCollisions();
		checkLives();
		
		}
		else{
		enemy();
		counter=0;
		}
		if(posX<=-26)
			posX=25;
		if(posX>=26)
			posX=-25;
		
		userplace->modelMatrix=glm::translate(glm::mat4(1.f), glm::vec3(-posX,posY,-posZ));
		userplace->update(elapsedTimeSec);
		glutKeyboardFunc(KeyboarCB);
		VisualObject::update( elapsedTimeSec );

	} // end update


	void checkLives(){
		for(unsigned int j = 1; j < children.size(); j++){
			VisualObject* temp=children[j];
			glm::vec3 v = temp->getWorldPosition();
				if(v.z>=25){
					lives--;
					cout<<"You lost a life!"<<endl;
					if(lives<=0){
						clearBoard();
						cout<<"You Lose! Hit 'r' to restart!"<<endl;
						cout<<"Your final score was: "<<score<<endl;
						running=false;
					break;
					}
					else{
						clearBoard();
						break;
					}
				
				}
		}
	}
	void clearBoard(){
		for(unsigned int j = 1; j < children.size();){
			children[j]->detachFromParent();
		}
	}
	void userPlace(){
		userplace= new Sphere(glm::vec4(128,0,128,255),1, 16,16);
		userplace->setShader(shaderGLUT);
		//addChild(tem0);
		userplace->modelMatrix=glm::translate(glm::mat4(1.f), glm::vec3(-posX,posY,-posZ));
		userplace->initialize();
	}
	void fire(){
		if(running){
		VisualObject* tem0= new Sphere();
		PhysicsController* pys= new PhysicsController();
		tem0->setShader(shaderGLUT);
		
		tem0->addController( pys);
		//glm::mat4 viewMatrix= glm::translate(glm::mat4(1.0f),);
		//glm::vec3 wep = viewMatrix[3].xyz;
		
		pys->launch(glm::vec3( -posX, posY, -(posZ+1) ),glm::vec3(0,0,-1),20.0f);
		addChild(tem0);
		tem0->initialize();
		//pys->launch(glm::vec3(0,0,12),glm::vec3(0,0,-1),20.f);
		//tem0->addController( new PointPoint(posX,posY,posZ));
		
		}
		
	}
	void checkCollisions(){
		
		for (unsigned int i = 1; i <  children.size(); i++) {
			//glm::vec3 check = children[i]->getWorldPosition();
			VisualObject* temp=children[i];
			for(unsigned int j = 1; j < children.size(); j++){
				if(close(i,j)){
					VisualObject* ref=children[j];
					temp->detachFromParent();
					ref->detachFromParent();
					if(running)
					score++;
					//children[i]->detachFromParent();
					//children[j]->detachFromParent();
				}
			}
			if(children[i]->getWorldPosition().z<=-26)
				temp->detachFromParent();
		}
	}
	bool close(unsigned int i, unsigned int j){
		glm::vec3 id=children[i]->getWorldPosition();
		glm::vec3 jd=children[j]->getWorldPosition();
		if(/*i!=j*/id!=jd && sqrt(pow(id.x-jd.x,2) +pow(id.y-jd.y,2)+pow(id.z-jd.z,2))<2)
			return true;
		return false;
	}
	void reset(){
		lives=3;
		if(running)
		cout<<"You destroyed "<<children.size()-1<<" objects. You pansy."<<endl;
		clearBoard();
		score=0;
		posX=0;
		running=true;
	}
	void enemy(){
		VisualObject* tem0= new Teapot(glm::vec4(1,0,0,0), 3);
		tem0->modelMatrix=glm::rotate(glm::mat4(1), 90.f, glm::vec3(0,0,1));
		PhysicsController* pys= new PhysicsController(0.f);
		tem0->setShader(shaderGLUT);
		addChild(tem0);
		tem0->addController( pys);
		//tem0->addController(new SpinnerController(glm::vec3(1.0f),glm::vec3(1,0,0),25));
		
		pys->launch(glm::vec3( (rand() % 50 + 1)-25, posY, -25 ),glm::vec3(0,0,1),3.f);
		tem0->initialize();
	}

	void setViewPoint( )
	{
		glm::mat4 viewMatrix;
		switch (view) {
		case 1:
			viewMatrix= glm::translate(glm::mat4(1.0f),glm::vec3( posX, posY, posZ ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			user=false;
			break;
		case 2:
			viewMatrix=glm::lookAt(glm::vec3( 0, 60, 0 ),glm::vec3( 0.0f, 0.0f, 0.0f ),glm::vec3( 0.0f, 0.0f, -1.0f ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			user=true;
		break;
		default:
			viewMatrix= glm::translate(glm::mat4(1.0f),glm::vec3( posX, posY, posZ ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		}
		
	
	}

	void setUpMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createFigureMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliaMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("View", menu0id); // Attach polygon Menu
		glutAddSubMenu("Polygon",menu1id);
		glutAddSubMenu("Front Face",menu2id);
		glutAddSubMenu("Point Size",menu3id);
		glutAddSubMenu("Line Width",menu4id);
		glutAddSubMenu("Antialiasing",menu5id);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	
	GLuint createFigureMenu(){
		GLuint menuId = glutCreateMenu(viewMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("View 1", 1);
		glutAddMenuEntry("View 2", 2);
		return menuId;
	}

}; // end zirkleacLab4

zirkleacProgram1* labClassPtr;

void viewMenu(int value)
{
	labClassPtr->view = value;
	cout << "View Point " << value << endl;
} // end figureMenu

void KeyboarCB(unsigned char Key, int x, int y)
{

	switch (Key) {
	/*	case 'w': case 'W':
		labClassPtr->posZ++;
		break;
	case 's': case'S':
		labClassPtr->posZ--;
		break;*/
	case ' ':
		labClassPtr->fire();
		break;
	case 'a': case'A':
		labClassPtr->posX++;
		break;
	case 'd': case'D':
		labClassPtr->posX--;
		break;
	case 'r': case 'R':
		labClassPtr->reset();
		break;
	default:
		break;
		//OpenGLApplicationBase::KeyboardCB(Key, x, y);
	}

} 

void SpecialKeyboardCB(int Key, int x, int y)
{
	switch (Key) {
	case GLUT_KEY_RIGHT:
		labClassPtr->posX--;
		break;
	case GLUT_KEY_LEFT:
		labClassPtr->posX++;
		break;
	/*case GLUT_KEY_UP:
		labClassPtr->posX++;

		break;
	case GLUT_KEY_DOWN:
		labClassPtr->posX--;
		*/
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Program 1" );
	zirkleacProgram1 pApp;
	labClassPtr = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main