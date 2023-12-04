#include <Entities/Terminal.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Terminal::Terminal()
{
}

Terminal::~Terminal()
{
}

void Terminal::onCreate()
{
	model = new Model(std::string("Assets/Models/Terminal/terminal.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 31.0f));

	OEntity::onCreate();
}

void Terminal::onUpdate(float deltaTime)
{
	timeValue += deltaTime * 0.25f;
	
	float speed = 1.5f;
	float heightMult = 0.1f;
	position.y += glm::sin(timeValue * speed) * heightMult * deltaTime;

	resetRotation();
	rotate(-timeValue * 0.5f, glm::vec3(0, 1, 0)); //y rotation

	glm::vec3 forward = glm::vec3(rotationMatrix[0][2], rotationMatrix[1][2], rotationMatrix[2][2]);
	forward.z *= -1.0f;
	glm::vec3 right = glm::vec3(rotationMatrix[0][0], rotationMatrix[1][0], rotationMatrix[2][0]);
	right.z *= -1.0f;
	glm::vec3 up = glm::vec3(0, 1, 0);

	graphicsEngine()->PushText3D(new Text3D("Lorem ipsum dolor sit amet,\n consectetur adipiscing elit. Praesent sollicitudin est elit, a semper sem\nviverra venenatis. Morbi facilisis sollicitudin tortor non feugiat. Maecenas orci lorem, lobortis nec\nauctor vel, venenatis ac sem. Phasellus eu mauris viverra, efficitur lorem ut, tempor libero. Sed eu\nrisus et sem fermentum tincidunt. Curabitur semper semper dui ut tristique. Etiam mattis\ncondimentum quam non aliquet. Cras lacinia, tortor eget vulputate maximus, tortor est condimentum\nquam, eget convallis elit leo ut dui. Ut viverra fringilla nisl et dapibus.\n\nVivamus id sapien varius, luctus quam porttitor, tempor magna.Ut accumsan, lorem et suscipit\nscelerisque, lacus neque interdum ex, et maximus risus ligula vitae velit.In hac habitasse platea\ndictumst.Curabitur eleifend rutrum diam vel bibendum.Aliquam id dolor metus.Fusce molestie gravida\nmolestie.Fusce varius id leo non malesuada.Cras quis est eu quam luctus imperdiet.Quisque efficitur\nut lectus condimentum consequat.\n\nDonec eget diam venenatis enim placerat efficitur ac eget urna.Ut dictum, dui ut luctus ornare, velit\njusto tristique odio, ac pharetra augue purus sit amet urna.Etiam rutrum blandit metus.Pellentesque\ndapibus augue dolor, quis malesuada est suscipit a.Praesent faucibus augue a dolor consectetur, vitae\nvehicula ex aliquam.Praesent vitae odio mollis, ultricies augue in, interdum magna.Cras pretium purus\nvel ligula varius cursus.Proin blandit nec massa eget accumsan.Sed massa augue, finibus sed purus\nnon, cursus eleifend neque.Proin id tincidunt massa, id suscipit ante.\n\nCras aliquet augue eu tellus placerat ornare.Nam aliquam tempus augue, non tempus ex tempor a.\nPraesent placerat pretium faucibus.Suspendisse vestibulum mollis iaculis.Nulla facilisi.Sed non\nmalesuada massa, ut fermentum purus.Duis lobortis lobortis enim, sed maximus nisi pulvinar aliquet.\nSed viverra pulvinar velit sed porta.Aliquam a quam eu augue egestas ultrices.",
		position + (-forward * 0.5891f) + (-right * 0.5f) + (up * 0.54f), rotationMatrix, 0.0005f, glm::vec3(0.5, 0.8f, 0.2f))); //the graphics manager needs to transform it to 3d space
}

void Terminal::onDraw()
{
	OEntity::onDraw();
}
