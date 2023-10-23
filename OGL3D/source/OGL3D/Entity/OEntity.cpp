#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMathStructs.h>
#include <OGL3D/Window/OWindow.h>

OEntity::OEntity() //constructor
{
}

OEntity::~OEntity() //destructor
{
}

void OEntity::onUpdate(f32 deltaTime)
{
	//OGL3D_INFO("test" << std::endl);
}

void OEntity::onDraw()
{
	OMat4 world, projection, temp; //instantiating 4x4 matrices
	//due to matrix multiplication, we can do each operation (scale, rotate, translate) one at a time and multiply the results.
	//starting with scale
	temp.setIdentity();
	temp.setScale(scale);
	world *= temp;

	//then doing rotation
	temp.setIdentity();
	temp.setRotationZ(rotation.z);
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(rotation.y);
	world *= temp;

	temp.setIdentity();
	temp.setRotationX(rotation.x);
	world *= temp;

	//then doing translation
	temp.setIdentity();
	temp.setTranslation(OVec3(position.x, position.y, position.z));
	world *= temp;

	//multiplying it all by the projection matrix
	auto displaySize = display()->getInnerSize();
	float projectionMultiplier = 0.004f;
	projection.setOrthoLH(displaySize.width * projectionMultiplier, displaySize.height * projectionMultiplier, 0.0f, 1000.0f);

	UniformData data = { world, projection }; //putting the world matrix and the projection matrix in a struct
	m_uniform->setData(&data); //passing this data to OpenGL's uniform buffer




	graphicsEngine()->setFaceCulling(OCullType::BackFace); //sets the culling to hide the backfaces as opposed to front faces. It's insane to me that this isn't the default.
	graphicsEngine()->setWindingOrder(OWindingOrder::ClockWise); //sets the order in which the triangles get drawn, which influences where the colours end up
	graphicsEngine()->setVertexArrayObject(m_polygonVAO); //binds the vertex array in OpenGL with glBindVertexArray
	graphicsEngine()->setUniformBuffer(m_uniform, 0); //sets the uniform buffer and the slot in OpenGL with glBindBufferBase
	graphicsEngine()->setShaderProgram(m_shader); //sets the shader program in OpenGL with glUseProgram()


	graphicsEngine()->drawIndexedTriangles(OTriangleType::TriangleList, 36); //draws the list of triangles based on the type being passed and their indices
}

void OEntity::release(OEntity* p_entity) //releases the entity from the entity system
{
	m_entitySystem->removeEntity(p_entity);
}

OEntitySystem* OEntity::getEntitySystem() //returns the entity system
{
	return m_entitySystem;
}

void OEntity::setPosition(OVec3 newPosition)
{
	position = newPosition;
}

void OEntity::setRotation(OVec3 newRotation)
{
	rotation = newRotation;
}

void OEntity::setScale(OVec3 newScale)
{
	scale = newScale;
}

OGraphicsEngine* OEntity::graphicsEngine()
{
	return m_entitySystem->getGraphicsEngine();
}

OWindow* OEntity::display()
{
	return m_entitySystem->getWindowDisplay();
}
