#include <iostream>

#include <GL\glew.h> //needs to be before glfw include
#include <GL\glfw.h>

#include "OptionManager.h"
#include "InputHandler.h"

#define GameTitle "Game of Thrones, literally!"
#define TimeStep 0.01666666666 //60fps

int GLFWCALL shutDown();

bool running = true;

void main(void)
{
	OptionManager om;
	InputHandler input;		//input(om); for later use with button mapping/rebindable keys

	glfwInit(); //needs to be before glew calls
	
	//block deprecated openGL calls (fixed function pipeline < 3.0)
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);	//openGL 3.
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);	//openGL x.3
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	if(om.getFullscreen())
	{
		if ( !glfwOpenWindow(om.getResolutionX(), om.getResolutionY(), 0, 0, 0, 0, 24, 8, GLFW_FULLSCREEN))
		{
			std::cerr << "Could not create fullscreen game" << std::endl;
			glfwTerminate();
			return;
		}
	}
	else
	{
		if ( !glfwOpenWindow(om.getResolutionX(), om.getResolutionY(), 0, 0, 0, 0, 24, 8, GLFW_WINDOW)) 
		{
			std::cerr << "Could not create window" << std::endl;
			glfwTerminate();
			system("PAUSE");
			return;
		}
	}

	glfwSetWindowCloseCallback(&shutDown);
	glfwSetWindowTitle(GameTitle);


	glewExperimental = true;	//otherwise the openGL context doesn't seem to properly initialize and openGL related functions are null pointers. also needed for opengl core profile
	if (glewInit() != GLEW_OK)
	{		
		std::cerr << "Could not init glew" << std::endl;
		system("PAUSE");
		return;
	} 
	glGetError();		//glew is buggy and throws an openGL error no matter what, this handlies that error by ignoring it.

	glClearColor(0.5,0.5,0.5,0.5);
	glm::vec4 p1Scissor(0,0,om.getResolutionX(), om.getResolutionY());


	double oldTime = 0;

	while(running)
	{

		switch(glGetError())
		{
			case GL_INVALID_ENUM: std::cerr << "ogl error: GL_INVALID_ENUM" << std::endl; break;
			case GL_INVALID_VALUE: std::cerr << "ogl error: GL_INVALID_VALUE" << std::endl; break;
			case GL_INVALID_OPERATION: std::cerr << "ogl error: GL_INVALID_OPERATION" << std::endl; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: std::cerr << "ogl error: GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
			case GL_OUT_OF_MEMORY: std::cerr << "ogl error: GL_OUT_OF_MEMORY" << std::endl; break;
			case GL_STACK_UNDERFLOW: std::cerr << "ogl error: GL_STACK_UNDERFLOW" << std::endl; break;
			case GL_STACK_OVERFLOW: std::cerr << "ogl error: GL_STACK_OVERFLOW" << std::endl;break;
			case GL_NO_ERROR: 
			DEFAULT:
				double newTime = glfwGetTime();
			
			


				while ( oldTime < newTime )
				{
				//	update(TimeStep);
					oldTime += TimeStep;
				
				}

				//draw(TimeStep)

				glfwSwapBuffers(); //actually draws the frame
				glClear(GL_COLOR_BUFFER_BIT);
				
				if(input.esc)
					shutDown();
		}
	}
}

int GLFWCALL shutDown()
{
	running = false;
	return 0;
}