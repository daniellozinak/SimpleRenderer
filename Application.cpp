#include "Application.h"
#include "data.h"
#include "CallbackData.h"
#include "ComponentManager.h"
//init instance
Application Application::instance;

CallbackData &callback_instance = CallbackData::getInstance();


//temp functions until object loader not impelemted
std::vector<util::Vertex> loadSphere()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < sphere; i++)
	{
		VertexData vData = vertices_sphere[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

std::vector<util::Vertex> loadWorker()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < worker; i++)
	{
		VertexData vData = vertices_worker[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

std::vector<util::Vertex> loadBox()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < box; i++)
	{
		VertexData vData = vertices_box[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

std::vector<util::Vertex> loadSuzi()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < suzi; i++)
	{
		VertexData vData = vertices_suzi[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

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
	std::vector<util::Vertex>vert_worker = loadWorker();
	std::vector<util::Vertex>vert_sphere = loadSphere();
	std::vector<util::Vertex>vert_suzi = loadSuzi();
	std::vector<util::Vertex>vert_box = loadBox();


	m_renderer = new Renderer();
	Scene *scene = new Scene();

	Shader *mShaderPhong = new Shader("./VertexShader.glsl", "./FragmentShaderPhong.glsl");
	Shader *mShaderLambert = new Shader("./VertexShader.glsl", "./FragmentShaderLambert.glsl");
	Shader *mShaderStatic = new Shader("./VertexShader.glsl", "./FragmentShaderStatic.glsl");
	Shader *mShaderBlinn = new Shader("./VertexShader.glsl", "./FragmentShaderBlinn.glsl");
	Camera *m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));

	scene->setCamera(m_camera);
	scene->setLight(glm::vec3(15.0f, 4.5f, 0.0f));
	scene->addShader(mShaderPhong);
	scene->addShader(mShaderLambert);
	scene->addShader(mShaderStatic);
	scene->addShader(mShaderBlinn);

	Mesh *sphere = new Mesh(vert_sphere, vert_sphere.size(), mShaderBlinn);
	Mesh *worker = new Mesh(vert_worker, vert_worker.size(), mShaderBlinn);
	Mesh *suzi = new Mesh(vert_suzi, vert_suzi.size(), mShaderBlinn);
	Mesh *box = new Mesh(vert_box, vert_box.size(), mShaderBlinn);
	
	/*Object *ball0 = new Object();
	ball0->add(worker);
	ball0->setPosition(glm::vec3(7.0f, 1.0f, 0.0f));

	Object *ball1 = new Object();
	ball1->add(sphere);
	ball1->setPosition(glm::vec3(15.0f, 0.0f, 4.0f));*/

	Object * ball2 = new Object();
	ball2->add(suzi);
	ball2->setPosition(glm::vec3(15.0f, 0.5f, -4.0f));
	ball2->move(0.1f, MoveDirection::FORWARDS,m_camera->getLookDirection());
	ball2->changeSelected();
	
	Object * ball3 = new Object();
	ball3->add(box); 
	ball3->add(ball2);
	ball3->setPosition(glm::vec3(10.0f, 4.5f, 4.0f));
	ball3->changeSelected();
		/*
	ball3->add(ball0);
	ball3->add(ball2);
	ball3->add(ball1);
	
	ball3->setPosition(glm::vec3(10.0f, 4.5f, 4.0f));*/


	//ObjectManager &om = ObjectManager::getInstance();
	//om.addObject(ball3);

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

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
		{
			callback_instance.setMoving(!callback_instance.isMoving());
		}
		if (callback_instance.isMoving())
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_W){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::FORWARDS);}
		if (key == GLFW_KEY_S){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::BACKWARDS);}
		if (key == GLFW_KEY_A){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::LEFT);}
		if (key == GLFW_KEY_D){ callback_instance.getCamera()->move(callback_instance.getDelta(),MoveDirection::RIGHT);}

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