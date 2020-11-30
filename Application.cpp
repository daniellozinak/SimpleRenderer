#include "Application.h"
#include "data.h"
#include "CallbackData.h"
#include "ComponentManager.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Cubemap.h"

//init instance
Application Application::instance;

CallbackData &callback_instance = CallbackData::getInstance();
ComponentManager &component_manager = ComponentManager::getInstance();


//temp functions until object loader not impelemted


std::vector<util::Vertex> loadPlain()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < plain; i++)
	{
		VertexData vData = vertices_plain[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		glm::vec2 tempTexture = { vData.Texture[0],vData.Texture[1] };
		util::Vertex tempVert = { tempPos,tempNormal,tempTexture};
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

std::vector<util::Vertex> loadSphere()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < sphere; i++)
	{
		VertexNoTex vData = VERTICES[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

std::vector<util::Vertex>global_ball = loadSphere();


void Application::init() {

	glfwSetErrorCallback([](int err, const char * desc) {fputs(desc, stderr); });
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}


	m_window = glfwCreateWindow(WIDTH, HEIGHT, "SimpleRenderer", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLuint result = glewInit();

	if (GLEW_OK != result)
	{
		printf("ERROR: %s", glewGetErrorString(result));
		exit(EXIT_FAILURE);
	}


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::run()
{
	double startTime = glfwGetTime();
	double lastTime = startTime;

	this->init();
	this->initScene();


	m_renderer->enableDepth();

	while (!glfwWindowShouldClose(m_window))
	{
		startTime = glfwGetTime();

		m_renderer->render();
			
		glfwPollEvents();
			
		glfwSwapBuffers(m_window);

		callback_instance.setDelta(startTime - lastTime);

		lastTime = startTime;

		if (callback_instance.isMoving()) { glfwSetCursorPos(m_window, WIDTH / 2, HEIGHT / 2); }
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}



//TODO 2: move this to Scene class
void Application::initScene()
{
	std::vector<util::Vertex>vert_plain = loadPlain();
	std::vector<util::Vertex>vert_sphere = loadSphere();


	m_renderer = new Renderer();
	Scene *scene = new Scene();
	m_renderer->setScene(scene);
	callback_instance.setScene(scene);

	Shader *mShaderPhong = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPoint.glsl");
	Shader *mShaderTexture = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPointTexture.glsl");
	Shader* mShaderSkyBox = new Shader("./VertexShaderSkyBox.glsl", "./FragmentShaderSkyBox.glsl");

	Camera *m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	PointLight *pointLight = new PointLight(glm::vec3(15), "lights[1]", 0.002f, .03f, 0.0f);
	DirectionalLight *directionLight = new DirectionalLight(glm::vec3(8.0,3.0,-2.0), "lights[0]");
	//SpotLight *spotLight = new SpotLight(glm::vec3(5.0f), glm::vec3(1.0, 1.0, 1.0), "lights[0]", 0.55f);
	

	scene->setCamera(m_camera);
	scene->addShader(mShaderPhong);
	scene->addShader(mShaderTexture);
	scene->addShader(mShaderSkyBox);


	scene->addLight(directionLight, LightType::Directional);
	//scene->addLight(spotLight, LightType::Spot);
	scene->addLight(pointLight, LightType::Point);

	mShaderPhong->sendUniform(LIGHT_COUNT_UNIFROM, 2);
	mShaderTexture->sendUniform(LIGHT_COUNT_UNIFROM, 2);
	
	Mesh *sphere = new Mesh(vert_sphere, vert_sphere.size(), mShaderPhong);
	//Mesh *worker = new Mesh(vert_worker, vert_worker.size(), mShaderPhong);
	//Mesh *suzi = new Mesh(vert_suzi, vert_suzi.size(), mShaderPhong);
	//Mesh *box = new Mesh(vert_box, vert_box.size(), mShaderPhong);
	/*Mesh* plain = new Mesh(vert_plain, vert_plain.size(), mShaderPhong);*/

	Mesh* pln = new Mesh(vert_plain, vert_plain.size(), mShaderTexture);
	pln->addTexture("./Textures/mino.png");

	//create skybox
	Cubemap* skybox = new Cubemap("./Objects/skybox.obj", mShaderSkyBox);
	skybox->load();

	//add skybox
	scene->setSkyBox(skybox);

	/*scene->addMesh(sphere);
	scene->addMesh(worker);
	scene->addMesh(suzi);
	scene->addMesh(box);*/


	Object* ball = new Object();
	ball->setPosition(glm::vec3(8.0,1.0,-2.0));
	ball->add(sphere);


	Object* plainObject = new Object();
	plainObject->setPosition(glm::vec3(8.0, 2.0, 2.0));
	plainObject->add(pln);


	this->initCallbacks();
}

void Application::initCallbacks()
{
	//Camera isnt nullptr
	assert(callback_instance.getCamera());

	callback_instance.setDelta(0);

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
		if (callback_instance.isMoving())
		{
			callback_instance.getCamera()->lookAround(callback_instance.getDelta(), xpos - (WIDTH / 2), ypos - (HEIGHT / 2));
		}
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {

		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) 
		{
			callback_instance.setMoving(!callback_instance.isMoving());
		}
		if (callback_instance.isMoving())
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else if(!callback_instance.isMoving() && action == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			double xpos, ypos;

			glfwGetCursorPos(window, &xpos, &ypos);


			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			GLint x = xpos;
			GLint y = HEIGHT - ypos;

			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

			component_manager.selectObject(index);
			callback_instance.setIndex(index);


			glm::vec3 screenX = glm::vec3(x, y, depth);
			glm::mat4 view = callback_instance.getCamera()->getView();
			glm::mat4 projection = callback_instance.getCamera()->getProjection();
			glm::vec4 viewPort = glm::vec4(0, 0, WIDTH, HEIGHT);
			glm::vec3 position = glm::unProject(screenX, view, projection, viewPort);

			callback_instance.setPosition(position);
		}
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_W){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::FORWARDS);}
		if (key == GLFW_KEY_S){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::BACKWARDS);}
		if (key == GLFW_KEY_A){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::LEFT);}
		if (key == GLFW_KEY_D){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::RIGHT);}

		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && !callback_instance.isMoving())
		{
			if (callback_instance.getIndex() > 0)
			{
				Scene * scene = callback_instance.getScene();
				Object *newObject = scene->createNewObject(global_ball,callback_instance.getPosition());
				component_manager.addObject(newObject, callback_instance.getIndex());
				std::cout << "New object at : " << glm::to_string(callback_instance.getPosition()) << "\n";
			}
		}

		if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && !callback_instance.isMoving())
		{
			component_manager.removeObject(callback_instance.getIndex());
			callback_instance.setIndex(0);
		}

		for (Component *component : ComponentManager::getInstance().getObjects())
		{
			if (key == GLFW_KEY_UP) { component->move(callback_instance.getDelta(), MoveDirection::FORWARDS, callback_instance.getCamera()->getLookDirection()); }
			if (key == GLFW_KEY_DOWN) { component->move(callback_instance.getDelta(), MoveDirection::BACKWARDS, callback_instance.getCamera()->getLookDirection()); }
			if (key == GLFW_KEY_RIGHT) {}
			if (key == GLFW_KEY_LEFT) {}
		}
	});
}

Application &Application::getInstance()
{
	return instance;
}

Application::Application()
{
}