#include <Entities/TestEntity.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OMathStructs.h>
#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Window/OWindow.h>

TestEntity::TestEntity()
{

}

TestEntity::~TestEntity()
{
}

void TestEntity::onCreate()
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
		OVec3(0.35f,0.18f,0.28f),
		OVec3(0.17f,0.49f,0.70f),
		OVec3(0.92f,0.11f,0.62f),
		OVec3(0.41f,0.1f,0.82f),
		OVec3(0.1f,0.86f,0.91f),
		OVec3(1,0.22f,0.38f),
		OVec3(0.57f,0.92f,0.32f),
		OVec3(0.5f,0.8f,0.2f)
	};

	//list of each cube position along with the matching colour.
	Vertex verticesList[] =
	{
		//front
		{positionsList[0], texcoordsList[0] },
		{positionsList[1], texcoordsList[2] },
		{positionsList[2], texcoordsList[5] },
		{positionsList[3], texcoordsList[7] },

		//back
		{positionsList[4], texcoordsList[1] },
		{positionsList[5], texcoordsList[5] },
		{positionsList[6], texcoordsList[4] },
		{positionsList[7], texcoordsList[7] },

		//top
		{positionsList[1], texcoordsList[7] },
		{positionsList[6], texcoordsList[5] },
		{positionsList[5], texcoordsList[3] },
		{positionsList[2], texcoordsList[1] },

		//bottom
		{positionsList[7], texcoordsList[6] },
		{positionsList[0], texcoordsList[4] },
		{positionsList[3], texcoordsList[2] },
		{positionsList[4], texcoordsList[0] },

		//right
		{positionsList[3], texcoordsList[0] },
		{positionsList[2], texcoordsList[5] },
		{positionsList[5], texcoordsList[6] },
		{positionsList[4], texcoordsList[2] },

		//left
		{positionsList[7], texcoordsList[6] },
		{positionsList[6], texcoordsList[0] },
		{positionsList[1], texcoordsList[4] },
		{positionsList[0], texcoordsList[2] }
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
	m_polygonVAO = graphicsEngine()->createVertexArrayObject(
		{ //this first part creates the Vertex Buffer Description (OVertexBufferDesc)
			(void*)verticesList, //cube vertices (points + colour)
			sizeof(Vertex), //size of each vertex
			sizeof(verticesList) / sizeof(Vertex), //number of elements

			attribsList, //amount of position and texcoord elements
			sizeof(attribsList) / sizeof(OVertexAttribute) //OVertexAttribute is just a ui32, so I guess this is saying how many elements are in attribsList
		},

		{ //this second part creates the Index Buffer Description (OIndexBufferDesc)
			(void*)indicesList, //list of indices
			sizeof(indicesList) //size of the whole list (imma be real I don't get why this isn't divided by sizeof(ui32) to count the number of elements)
		}
		);

	//create the uniform buffer 
	m_uniform = graphicsEngine()->createUniformBuffer({
		sizeof(UniformData) //contains two OMat4's
		});

	//create the shader program
	m_shader = graphicsEngine()->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert", //basic vertex shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
			L"Assets/Shaders/BasicShader.frag" //basic fragmentation shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
		});
	m_shader->setUniformBufferSlot("UniformData", 0); //idk I'm lost and afraid
}

void TestEntity::onUpdate(f32 deltaTime)
{
	OEntity::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;

	rotation.x += 0.3f * deltaTime; //increasing the rotation every frame
	rotation.y += 0.3f * deltaTime; //increasing the rotation every frame
	rotation.z += 0.3f * deltaTime; //increasing the rotation every frame
}

void TestEntity::onDraw()
{
	OEntity::onDraw();
}
