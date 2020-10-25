#include "Application.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "data.h"


//Include GLM  
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>


float points[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};


float colors[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};


std::vector<util::Vertex> floatToVertex(float points[], float color[], unsigned count)
{
	std::vector<util::Vertex> toReturn;
	for (unsigned i = 0; i < count / 3; i++)
	{
		glm::vec3 tempPos = { points[i*(3) + 0],points[i*(3) + 1],points[i*(3) + 2] };
		glm::vec3 tempCol = { color[i*(3) + 0] ,color[i*(3) + 1] ,color[i*(3) + 2] };
		util::Vertex tempVert = { tempPos,tempCol };
		toReturn.push_back(tempVert);
	}

	return toReturn;
}

std::vector<util::Vertex> vertexToVertex()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < pocetPrvku; i++)
	{
		VertexData vData = VERTICES[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}


const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 fragmentColor;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"uniform vec3 lightPosition;"
"void main () {"
"	  mat4 mvp =  projectionMatrix * viewMatrix * modelMatrix;"
"     gl_Position = mvp * vec4(vp, 1.0);"
"	  fragmentColor = vc ;"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 fragmentColor;"
"void main () {"
"     frag_colour = vec4 (fragmentColor, 1.0);"
"}";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow *window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void checkError() {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl Error] " << error << "\n";
	}
	std::cout << "No error\n";
}



int main(void)
{
	//108
	std::vector<util::Vertex>vert = vertexToVertex();

	Application &app = Application::getInstance();
	ObjectManager &om = ObjectManager::getInstance();

	//init window
	GLFWwindow* window;

	auto err_callback_lamda = [](int err, const char * desc) {fputs(desc, stderr); };

	app.init(window, err_callback_lamda);


	//Camera mCam = new Camera();
	Shader *mShader = new Shader();
	Camera *cam = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0), mShader);
	mShader->setCamera(cam);
	cam->attach(mShader);
	cam->update();
	mShader->linkProgram(vertex_shader, fragment_shader);
	mShader->sendUniform("lightPosition", glm::vec3(10, 10, 10));



	Object ball = Object(vert, vert.size());
	ball.move(glm::vec3(10.0f, 1.0f, 0.0f));
	ball.setShader(mShader);

	Object ball1 = Object(vert, vert.size());
	ball1.move(glm::vec3(8.0f, 1.0f, 4.0f));
	ball1.setShader(mShader);

	om.addObject(ball);
	om.addObject(ball1);

	app.run(window, om, cam);

	//OpenGL ma pravotocivy system

	delete window;
	delete mShader;
	delete cam;

}