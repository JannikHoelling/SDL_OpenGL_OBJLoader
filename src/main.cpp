#include "main.h"
#include "GLShader.h"
#include "Camera.h"
#include "Mesh.h"
#include "OBJLoader.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const bool useAntialiasing = true;

const char* windowTitle = "SDL_OpenGL_OBJLoader";

//SDL
SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

//OpenGL
GLuint shaderProgram = 0;

// TODO: Move to Camera class
glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;
GLint projectionMatrixLocation;
GLint viewMatrixLocation;

//TEST
//GLuint vbo;
//glm::vec3 test = glm::vec3(0.0f, 0.0f, 0.0f);
std::vector<glm::vec3> test { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 0.0f, 0.0f) };

Camera cam = Camera(60.0f, 0.0f, 0.25f, 55.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
Mesh m;
//std::vector<int> v { 34,23 };

bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		//Anti Aliasing
		if(useAntialiasing) {
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		}

		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		//Create window
		gWindow = SDL_CreateWindow( windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			return false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext( gWindow );

			if( gContext == NULL )
			{
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				return false;
			}
			else
			{

				std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
				std::cout << "OpenGL Renderer:" << glGetString(GL_RENDERER) << std::endl;
				std::cout << "OpenGL Version:" << glGetString(GL_VERSION) << std::endl;
				std::cout << "Glew Version:" << glewGetString(GLEW_VERSION) << std::endl;

				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if(glewError != GLEW_OK)
				{
					printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );

				}
				else {
					printf("GLEW Init: Success!\n");
				}

				//Use Vsync
				if(SDL_GL_SetSwapInterval( 1 ) < 0)
				{
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				if(!initShaders())
				{
					std::cout << "Unable to initialize Shaders!" << std::endl;
					return false;
				}
			}
		}
	}

	return true;
}

bool initShaders() {
    shaderProgram = glCreateProgram();
	glCheckError(glGetError(), "Create Program");

	GLint vertexShader = loadVertexShader("vertex.vert");
	GLint fragmentShader = loadFragmentShader("fragment.frag");

    shaderProgram = loadProgram(vertexShader, fragmentShader);
    glCheckError(glGetError(), "Load Program");

	//Get locations of view and projection matrices
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");

    //m = Mesh(test);
    m = loadOBJ();

    // VBO
    //glGenBuffers(1, &vbo );
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &test, GL_DYNAMIC_DRAW);

	if(projectionMatrixLocation < 0 || viewMatrixLocation < 0) {
		printf("Matrix Locations not found in program!\n");
		return false;
	}

    return true;
}

void handleKeys( unsigned char key, int x, int y )
{
    if( key == 'p' )
	{
		Screenshot(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "test.bmp");
	}
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &cam.projectionMatrix[0][0]);
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &cam.viewMatrix[0][0]);

    m.render();
    glCheckError(glGetError(), "Render Mesh");

    glUseProgram(0);
}

void update() {
    cam.camAngle += 0.05f;
    cam.position = glm::vec3(cos(cam.camAngle) * 1, 0.25f , sin(cam.camAngle) * 1);

	cam.viewMatrix = glm::translate(cam.viewMatrix, cam.position);
	cam.viewMatrix = glm::lookAt(cam.position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void close()
{
	//Deallocate program
	glDeleteProgram( shaderProgram );

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and creaŘte window
	if(!init()){
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Enable text input
		SDL_StartTextInput();

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				//Handle keypress with current mouse position
				else if( e.type == SDL_TEXTINPUT )
				{
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					handleKeys( e.text.text[ 0 ], x, y );
				}
			}

			update();

			render();


			//Update screen
			SDL_GL_SwapWindow( gWindow );
		}

		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	close();

	std::getchar();

	return 0;
}

void Screenshot(int x, int y, int w, int h, const char * filename)
{
    glFlush();
    unsigned char * pixels = new unsigned char[w*h*4]; // 4 bytes for RGBA
    glReadPixels(x,y,w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    SDL_Surface * surf = SDL_CreateRGBSurfaceFrom(pixels, w, h, 8*4, w*4, 0,0,0,0);
    SDL_SaveBMP(surf, filename);

    SDL_FreeSurface(surf);
    delete [] pixels;
}
