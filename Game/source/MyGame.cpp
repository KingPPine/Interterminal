#include <MyGame.h>
#include <OGL3D/Entity/OEntitySystem.h>
#include <Entities/Terminal.h>
#include <Entities/Cube2.h>
#include <Entities/MyPlayer.h>
#include <Entities/Floor.h>
#include <Entities/Wall.h>
#include <Entities/Bed.h>
#include <Entities/Chain.h>

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	OGame::onCreate(); //calls OGame's onCreate

	//playing background music
	//GameConstants::soundEngine->play2D("Assets/Music/THIS IS MY CASTLE!.mp3", true);

	player = getEntitySystem()->createEntity<MyPlayer>();
	player->setPosition(glm::vec3(0.0f, 0.0f, 8.0f));

	//the light cube
	Cube2* cube2 = getEntitySystem()->createEntity<Cube2>();
	cube2->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	cube2->setScale(glm::vec3(0.2f));

	//floor
	Floor* floor = getEntitySystem()->createEntity<Floor>();
	floor->setPosition(glm::vec3(0.0f, -1.8f, 0.0f));

	//walls
	Wall* wall = getEntitySystem()->createEntity<Wall>(); //wall in front
	wall->setPosition(glm::vec3(0.0f, 1.2f, -10.0f)); // height of the floor + 3 (-1.8 + 3 = 1.2)
	wall->rotate(1.5708f, glm::vec3(1, 0, 0));

	wall = getEntitySystem()->createEntity<Wall>(); //wall behind
	wall->setPosition(glm::vec3(0.0f, 1.2f, 10.0f)); // height of the floor + 3 (-1.8 + 3 = 1.2)
	wall->rotate(1.5708f, glm::vec3(1, 0, 0));
	wall->rotate(3.14159f, glm::vec3(0, 0, 1));

	wall = getEntitySystem()->createEntity<Wall>(); //wall to the right
	wall->setPosition(glm::vec3(10.0f, 1.2f, 0.0f)); // height of the floor + 3 (-1.8 + 3 = 1.2)
	wall->rotate(1.5708f, glm::vec3(1, 0, 0));
	wall->rotate(1.5708f, glm::vec3(0, 0, 1));

	wall = getEntitySystem()->createEntity<Wall>(); //wall to the left
	wall->setPosition(glm::vec3(-10.0f, 1.2f, 0.0f)); // height of the floor + 3 (-1.8 + 3 = 1.2)
	wall->rotate(1.5708f, glm::vec3(1, 0, 0));
	wall->rotate(-1.5708f, glm::vec3(0, 0, 1));

	Bed* bed = getEntitySystem()->createEntity<Bed>();
	bed->setPosition(glm::vec3(-7.5f, -1.25f, 8.0f));
	bed->rotate(1.5708f, glm::vec3(0,1,0));

	Chain* chain = getEntitySystem()->createEntity<Chain>();
	chain->setPosition(glm::vec3(-3.0f, 0.0f, 0.0f));


	//terminal
	terminal = getEntitySystem()->createEntity<Terminal>();
	terminal->setPosition(glm::vec3(0, -0.175f, 0));
	terminal->setScale(glm::vec3(0.7f));
}

void MyGame::onUpdate(float deltaTime)
{
	
}
