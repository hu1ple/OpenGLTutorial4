#pragma once
#include"Camera.h"
#include"deltaTime.h"
float lastX, lastY;
bool fisrtMouse = true;//抛弃第一帧标记
class Tutorial : public Window {
public:
	Tutorial(const char* title):Window(title)
	{
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

	}
	~Tutorial()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		delete pshader;
	}
	inline void RenderScreen() override final
	{
		glfwPollEvents();//告诉GLFW检查所有等待处理的事件和消息，包括操作系统和窗口系统中应当处理的消息。
										//如果有消息正在等待，它会先处理这些消息再返回；否则该函数会立即返回。
		glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		this->pshader->UseProgram();

		float timeValue = glfwGetTime();          //随时间改变颜色
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		this->pshader->Set4Float("Color", 0.0f, greenValue, 0.0f, 1.0f);
		//***********************
		//矩阵变换
		glm::mat4 transform = glm::mat4(1.0f);
		
		
		transform = glm::rotate(transform, timeValue * glm::radians(30.0f),
			glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f)); //缩小十倍
		transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
		this-> pshader->SetMatrix4fv("transform", transform);
		//**************************
		/*
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	*/

		//画cube
		
		this->pshaderWithColor->UseProgram();
		transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, timeValue * glm::radians(30.0f),
			glm::vec3(1.0f, 1.0f, 1.0f));      //绕对角线旋转
		this->pshaderWithColor->SetMatrix4fv("transform", transform);

		glm::mat4 proj = glm::perspective(glm::radians(pCamera ->GetZoom()), 
			static_cast<float>(WINDOWWIDTH) / static_cast<float>(WINDOWHEIGHT), 0.1f, 100.0f);
		this->pshaderWithColor->SetMatrix4fv("proj", proj);
		glm::mat4 view = pCamera->GetViewMatrix();			//view即是相机的lookAt矩阵
		this->pshaderWithColor->SetMatrix4fv("view", view);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		
		glfwSwapBuffers(this->window);  //交换缓冲区??
	}
	void initUI(int argc, char *argv[])
	{
		glfwSetKeyCallback(this->window, KeyCallback);   //
		glfwSetFramebufferSizeCallback(this->window, FramebufferSizeCallback);
		glfwSetCursorPosCallback(this->window, MouseCallback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetMouseButtonCallback(this->window, mouse_button_callback);
		//glutInit(&argc, argv);
		//glutMouseFunc(&MouseAction);
	}
	void CreateObjects()
	{
		this->CreateTriangle();
		this->CreateCube();
	}
	void CreateShaders()
	{
		pshader = new Shader("res/shaders/core.vs", "res/shaders/core.fs");
		pshaderWithColor = new Shader("res/shaders/corewithcolor.vs",
						"res/shaders/corewithcolor.fs");
	}
	bool IsWindowClosed()
	{
		return glfwWindowShouldClose(window);
	}

private:
	GLuint VAO = -1;
	GLuint VBO = -1;
	Shader* pshader;
	GLuint cubeVAO = -1;
	GLuint cubeVBO = -1;
	Shader* pshaderWithColor;
	static bool keys[1024];
	static  std::unique_ptr<Camera> pCamera;
	void CreateCube()
	{
		GLfloat vertices[] = { 
		 -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,														// front 
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		- 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		- 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
 
		- 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,															// back
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		- 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
 
		- 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,																							// left
		- 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		- 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		- 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		 - 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		- 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,	 1.0f, 1.0f, 0.0f,																							// right
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
          0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
 
		- 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,											// bottom
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		- 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		- 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
 
		- 0.5f,  0.5f, -0.5f, 0.0f, 1.0f ,1.0f,															// top
          0.5f,  0.5f, -0.5f, 0.0f, 1.0f ,1.0f,
          0.5f,  0.5f,  0.5f, 0.0f, 1.0f ,1.0f,
          0.5f,  0.5f,  0.5f, 0.0f, 1.0f ,1.0f,
		- 0.5f,  0.5f,  0.5f, 0.0f, 1.0f ,1.0f,
		- 0.5f,  0.5f, -0.5f, 0.0f, 1.0f ,1.0f

		};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void CreateTriangle()
	{
		GLfloat vertices[] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,0.0f, 1.0f, - 1.0f, 0.0f };
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)//键盘回调函数
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) {
				keys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				keys[key] = false;
			}
		}
		if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
			pCamera->ProcessKeyboard(FORWARD, deltaTime);
		}
		if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
			pCamera->ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
			pCamera->ProcessKeyboard(LEFT, deltaTime);
		}
		if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
			pCamera->ProcessKeyboard(RIGHT, deltaTime);
		}
		if (keys[GLFW_KEY_X])
			pCamera->MouseZoom();
	}
	static void FramebufferSizeCallback(GLFWwindow
		* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos)//鼠标回调函数
	{
		
		GLfloat xOffset, yOffset;
		if (fisrtMouse)
		{
			lastX = xPos;
			lastY = yPos;
			fisrtMouse = false;
		}
		xOffset = xPos - lastX;
		yOffset = lastY - yPos;			//这里是相反的，因为y坐标的范围是从下往上的
		lastX = xPos;
		lastY = yPos;					
		pCamera->ProcessMouseMove(xOffset, yOffset);	//处理相机的变化
	}
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)//滚轮实现缩放的回调函数
	{
		pCamera->ProcessMouseZoom(xoffset, yoffset);
	}
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
			pCamera->MouseZoom();
		}
	}
	/*
	static void MouseAction(int button, int state, int x, int y)
	{
		std::cout << "you clicked！" << std::endl;
		if (button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
		{
			pCamera->MouseZoom();
			std::cout << "you clicked！" << std::endl;
		}
	}
	*/
};

std::unique_ptr<Camera> Tutorial::pCamera = std::unique_ptr<Camera>(new
	Camera(glm::vec3(0.0f, .0f, 5.0f)));
bool Tutorial::keys[1024] = { false };





