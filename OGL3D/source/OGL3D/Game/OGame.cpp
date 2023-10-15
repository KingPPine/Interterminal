#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>
#include <OGL3D/Entity/OEntitySystem.h>

struct UniformData //data struct to pass to the uniform buffer
{
	OMat4 world; //the matrix of world coordinates (scale, rotation, translation)
	OMat4 projection; //the projection matrix
};

struct Vertex //data struct for a vertex, includes a position and a color
{
	OVec3 position;
	OVec3 texcoord;
};

OGame::OGame() //constructor
{
	//make_unique is good for safe memory allocation of new objects. I think...
	//explanation page here: https://pvs-studio.com/en/docs/warnings/v824/
	m_graphicsEngine = std::make_unique<OGraphicsEngine>(); //initializes the graphics engine to a unique pointer
	m_display = std::make_unique<OWindow>(); //initializes the display window to a unique pointer, calling the constructor
	m_entitySystem = std::make_unique<OEntitySystem>(); //initializes the entity system to a unique pointer

	m_display->makeCurrentContext(); //calls makeCurrentContext() in CWin32Window.cpp

	m_graphicsEngine->setViewport(m_display->getInnerSize()); //sets the viewport to the size defined in m_display within its constructor
}

OGame::~OGame() //destructor
{
}

void OGame::onCreate()
{
	//list of vertex positions for the cube
	OVec3 positionsList[] =
	{
		//front face
		OVec3(-0.5f, -0.5f, -0.5f), //0
		OVec3(-0.5f, 0.5f, -0.5f), //1
		OVec3(0.5f, 0.5f, -0.5f), //2
		OVec3(0.5f, -0.5f, -0.5f), //3

		//back face
		OVec3(0.5f, -0.5f, 0.5f), //4
		OVec3(0.5f, 0.5f, 0.5f), //5
		OVec3(-0.5f, 0.5f, 0.5f), //6
		OVec3(-0.5f, -0.5f, 0.5f) //7
	};

	//list of possible colours for the cube. For some reason the tutorial did a 2-dimensional vertex, but I was able to adapt this to RGB
	OVec3 texcoordsList[] =
	{
		//list of colours
		OVec3(0,0,1),
		OVec3(0,1,0),
		OVec3(0,1,1),
		OVec3(1,0,0),
		OVec3(1,0,1),
		OVec3(1,1,0),
		OVec3(1,1,1),
		OVec3(0.5f,0.8f,0.2f)
	};

	//list of each cube position along with the matching colour.
	Vertex verticesList[] =
	{
		//front
		{positionsList[0], texcoordsList[0] },
		{positionsList[1], texcoordsList[1] },
		{positionsList[2], texcoordsList[2] },
		{positionsList[3], texcoordsList[3] },

		//back
		{positionsList[4], texcoordsList[4] },
		{positionsList[5], texcoordsList[5] },
		{positionsList[6], texcoordsList[6] },
		{positionsList[7], texcoordsList[7] },

		//top
		{positionsList[1], texcoordsList[0] },
		{positionsList[6], texcoordsList[1] },
		{positionsList[5], texcoordsList[2] },
		{positionsList[2], texcoordsList[3] },

		//bottom
		{positionsList[7], texcoordsList[4] },
		{positionsList[0], texcoordsList[5] },
		{positionsList[3], texcoordsList[6] },
		{positionsList[4], texcoordsList[7] },

		//right
		{positionsList[3], texcoordsList[0] },
		{positionsList[2], texcoordsList[1] },
		{positionsList[5], texcoordsList[2] },
		{positionsList[4], texcoordsList[3] },

		//left
		{positionsList[7], texcoordsList[4] },
		{positionsList[6], texcoordsList[5] },
		{positionsList[1], texcoordsList[6] },
		{positionsList[0], texcoordsList[7] }
	};

	//The index list for the cube. This tells OpenGL in what order to draw each triangle (if I understand correctly)
	ui32 indicesList[] =
	{
		//front
		0,1,2,
		2,3,0,

		//back
		4,5,6,
		6,7,4,

		//top
		8,9,10,
		10,11,8,

		//bottom
		12,13,14,
		14,15,12,

		//right
		16,17,18,
		18,19,16,

		//left
		20,21,22,
		22,23,20
	};

	//clarifies the size of the attributes we're passing to OpenGL so that it knows how to parse the list
	OVertexAttribute attribsList[] = {
		//sizeof() tells us the actual size of the element.
		//Since OVec3 is a collection of 3 floats, the resulting size is 3 in each case.
		//I could change the first evaluation to sizeof(OVec2) if I just want to process 2 elements
		sizeof(OVec3) / sizeof(f32),//position
		sizeof(OVec3) / sizeof(f32)	//texcoord
	};

	//create the vertex array with all the components we've set up so far
	m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
		{ //this first part creates the Vertex Buffer Description (OVertexBufferDesc)
			(void*)verticesList, //cube vertices (points + colour)
			sizeof(Vertex), //size of each vertex
			sizeof(verticesList) /sizeof(Vertex), //number of elements

			attribsList, //amount of position and texcoord elements
			sizeof(attribsList) / sizeof(OVertexAttribute) //OVertexAttribute is just a ui32, so I guess this is saying how many elements are in attribsList
		},

		{ //this second part creates the Index Buffer Description (OIndexBufferDesc)
			(void*) indicesList, //list of indices
			sizeof(indicesList) //size of the whole list (imma be real I don't get why this isn't divided by sizeof(ui32) to count the number of elements)
		}
	);

	//create the uniform buffer 
	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData) //contains two OMat4's
		});

	//create the shader program
	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert", //basic vertex shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
			L"Assets/Shaders/BasicShader.frag" //basic fragmentation shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
		});
	m_shader->setUniformBufferSlot("UniformData", 0); //idk I'm lost and afraid
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

	auto deltaTime = (f32)elapsedSeconds.count(); //I think this turns it from a time point to a float of seconds

	//calling the General Update, and Entity System Update
	onUpdate(deltaTime); //in OGame and MyGame to help separate regular update instructrions from the matrix stuff in here
	m_entitySystem->update(deltaTime); //in OEntitySystem, which calls the update method of every entity in the game

	m_scale += 0.3f * deltaTime; //increasing this scale value every frame
	auto currentScale = abs(sin(m_scale)); //creating a current scale by capping the value with a sine function

	OMat4 world, projection, temp; //instantiating 4x4 matrices
	//due to matrix multiplication, we can do each operation (scale, rotate, translate) one at a time and multiply the results.
	//starting with scale
	temp.setIdentity();
	temp.setScale(OVec3(1, 1, 1));
	world *= temp;

	//then doing rotation
	temp.setIdentity();
	temp.setRotationZ(m_scale);
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_scale);
	world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_scale);
	world *= temp;
	
	//then doing translation
	temp.setIdentity();
	temp.setTranslation(OVec3(0, 0, 0));
	world *= temp;

	//multiplying it all by the projection matrix
	auto displaySize = m_display->getInnerSize();
	projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f);

	UniformData data = { world, projection }; //putting the world matrix and the projection matrix in a struct
	m_uniform->setData(&data); //passing this data to OpenGL's uniform buffer



	m_graphicsEngine->clear(OVec4(0.26f, 0.75f, 0.58f, 1)); //clears the screen with a specified colour

	m_graphicsEngine->setFaceCulling(OCullType::BackFace); //sets the culling to hide the backfaces as opposed to front faces. It's insane to me that this isn't the default.
	m_graphicsEngine->setWindingOrder(OWindingOrder::ClockWise); //sets the order in which the triangles get drawn, which influences where the colours end up
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO); //binds the vertex array in OpenGL with glBindVertexArray
	m_graphicsEngine->setUniformBuffer(m_uniform, 0); //sets the uniform buffer and the slot in OpenGL with glBindBufferBase
	m_graphicsEngine->setShaderProgram(m_shader); //sets the shader program in OpenGL with glUseProgram()
	m_graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList, 36); //draws the list of triangles based on the type being passed and their indices

	m_display->present(false); //this puts everything on our display. false means no vsync.
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
