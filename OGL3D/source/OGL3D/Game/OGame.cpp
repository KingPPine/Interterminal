#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Entity/OEntitySystem.h>
#include <GameConstants.h>

#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

OGame::OGame() //constructor
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(GameConstants::screenWidth, GameConstants::screenHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	//make_unique is good for safe memory allocation of new objects. I think...
	//explanation page here: https://pvs-studio.com/en/docs/warnings/v824/
	m_graphicsEngine = std::make_unique<OGraphicsEngine>(); //initializes the graphics engine to a unique pointer
	//m_display = std::make_unique<OWindow>(); //initializes the display window to a unique pointer, calling the constructor
	m_entitySystem = std::make_unique<OEntitySystem>(this); //initializes the entity system to a unique pointer

	//m_display->makeCurrentContext(); //calls makeCurrentContext() in CWin32Window.cpp

	//m_graphicsEngine->setViewport(m_display->getInnerSize()); //sets the viewport to the size defined in m_display within its constructor
	m_graphicsEngine->initializeFreeType();

	maxFPS = 0; //0 means the framerate isn't capped
}

OGame::~OGame() //destructor
{
}

void OGame::run()
{
	onCreate();
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		onUpdateInternal();

		//RenderText(shader, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent sollicitudin est elit, a semper sem\nviverra venenatis. Morbi facilisis sollicitudin tortor non feugiat. Maecenas orci lorem, lobortis nec\nauctor vel, venenatis ac sem. Phasellus eu mauris viverra, efficitur lorem ut, tempor libero. Sed eu\nrisus et sem fermentum tincidunt. Curabitur semper semper dui ut tristique. Etiam mattis\ncondimentum quam non aliquet. Cras lacinia, tortor eget vulputate maximus, tortor est condimentum\nquam, eget convallis elit leo ut dui. Ut viverra fringilla nisl et dapibus.\n\nVivamus id sapien varius, luctus quam porttitor, tempor magna.Ut accumsan, lorem et suscipit\nscelerisque, lacus neque interdum ex, et maximus risus ligula vitae velit.In hac habitasse platea\ndictumst.Curabitur eleifend rutrum diam vel bibendum.Aliquam id dolor metus.Fusce molestie gravida\nmolestie.Fusce varius id leo non malesuada.Cras quis est eu quam luctus imperdiet.Quisque efficitur\nut lectus condimentum consequat.\n\nDonec eget diam venenatis enim placerat efficitur ac eget urna.Ut dictum, dui ut luctus ornare, velit\njusto tristique odio, ac pharetra augue purus sit amet urna.Etiam rutrum blandit metus.Pellentesque\ndapibus augue dolor, quis malesuada est suscipit a.Praesent faucibus augue a dolor consectetur, vitae\nvehicula ex aliquam.Praesent vitae odio mollis, ultricies augue in, interdum magna.Cras pretium purus\nvel ligula varius cursus.Proin blandit nec massa eget accumsan.Sed massa augue, finibus sed purus\nnon, cursus eleifend neque.Proin id tincidunt massa, id suscipit ante.\n\nCras aliquet augue eu tellus placerat ornare.Nam aliquam tempus augue, non tempus ex tempor a.\nPraesent placerat pretium faucibus.Suspendisse vestibulum mollis iaculis.Nulla facilisi.Sed non\nmalesuada massa, ut fermentum purus.Duis lobortis lobortis enim, sed maximus nisi pulvinar aliquet.\nSed viverra pulvinar velit sed porta.Aliquam a quam eu augue egestas ultrices.",
		//    0.0f, 1040.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return;
}

void OGame::onCreate()
{
	
}

void OGame::onUpdateInternal()
{
	//computing delta time
	auto currentTime = std::chrono::system_clock::now(); //current point in time
	auto elapsedSeconds = std::chrono::duration<double>(); //initializing a duration at 0

	//m_previousTime is a "chrono::time_point". time_since_epoch() returns the the time point since the start of its clock. 
	//basically we're checking that we're passed the first frame.
	if (m_previousTime.time_since_epoch().count()) 
		elapsedSeconds = currentTime - m_previousTime; //difference in time between frames
	m_previousTime = currentTime; //setting the previous time for the next frame

	auto deltaTime = (float)elapsedSeconds.count(); //I think this turns it from a time point to a float of seconds
	framerateTimer += elapsedSeconds.count();


	//calling the General Update, and Entity System Update
	onUpdate(deltaTime); //in OGame and MyGame to help separate regular update instructions from the matrix stuff in here
	m_entitySystem->update(deltaTime); //in OEntitySystem, which calls the update method of every entity in the game
	//m_display->update(); //in CWin32Window.cpp, perform any updates needed for the window

	if (maxFPS <= 0 || framerateTimer > 1.0f / maxFPS)
	{
		m_graphicsEngine->EnableDepthTest();
		//m_graphicsEngine->clear(OVec4(0.26f, 0.75f, 0.58f, 1)); //clears the screen with a specified colour
		m_graphicsEngine->clear(OVec4(0.7f, 0.2f, 0.2f, 1)); //clears the screen with a specified colour
		m_entitySystem->draw(); //in OEntitySystem, which calls the draw method of every entity in the game


		m_graphicsEngine->DisableDepthTest();
		//Text2D* sampleText = new Text2D("FPS: " + std::to_string((int)(1.0f / framerateTimer)), glm::vec3(GameConstants::screenWidth - 300,GameConstants::screenHeight - 40, 0), 0.3f, glm::vec3(0.5, 0.8f, 0.2f));
		//Text2D* sampleText = new Text2D("FPS: " + std::to_string((int)(1.0f / framerateTimer)), glm::vec3(200, 200, 0), 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
		//Text2D* sampleText = new Text2D("FPS: 200.00005578", glm::vec3(0.0f, 1040.0f, 0), 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		//m_graphicsEngine->PushText(sampleText);

		//m_graphicsEngine->RenderAllText();

		m_graphicsEngine->RenderText2("FPS: 200.00005578", 0.0f, 1040.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

		//m_display->present(false); //this puts everything on our display. false means no vsync.

		framerateTimer = 0;
	}

	//Calling the input manager update at the end of the frame, as it prepares updates for the next frame
	GameConstants::inputManager->update();
}

void OGame::onQuit()
{
}

void OGame::quit()
{
	m_isRunning = false; //tells CWin32Game.cpp to quit the app
}

OEntitySystem* OGame::getEntitySystem()
{
	return m_entitySystem.get();
}

OGraphicsEngine* OGame::getGraphicsEngine()
{
	return m_graphicsEngine.get();
}

/*OWindow* OGame::getWindowDisplay()
{
	return m_display.get();
}*/

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}