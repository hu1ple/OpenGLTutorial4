#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat ZOOM = 45.0f;
const GLfloat SPEED = 10.f;
const GLfloat SENSITIVITY = 0.05f;
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) :front(glm::vec3(0.0f, 0.0f
		, -1.0f)), zoom(ZOOM), speed(SPEED),sensitivity(SENSITIVITY)
	{
		this->position = position;		//位置
		this->worldUp = up;				//上向量
		this->yaw = yaw;				//俯仰角
		this->pitch = pitch;			//
	}
	glm::mat4 GetViewMatrix()   //返回lookAt向量
	{
		return glm::lookAt(position, position + front, up);

	}

	GLfloat GetZoom()
	{
		return this->zoom;
	}
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)		//处理键盘按键，计算相机的位置
	{
		float velocity = this->speed * deltaTime;
		if (direction == FORWARD) {
			this -> position += this -> front * velocity;
		}
		if (direction == BACKWARD) {
			this->position -= this->front * velocity;
		}
		if (direction ==RIGHT) {
			this->position += this->right * velocity;
		}
		if (direction ==LEFT) {
			this->position -= this->right * velocity;
		}
	}
	void ProcessMouseMove(GLfloat xOffset, GLfloat yOffset)	//处理鼠标变换，计算相机的方向
	{
		xOffset *= sensitivity;
		yOffset *= sensitivity;
		this->yaw += xOffset;
		this->pitch += yOffset;
		this->updataCameraVectors();   //更新相机的front，up，right
	}
	void ProcessMouseZoom(double xoffset, double yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

	void MouseZoom()
	{
		if (this->state)
		{	//this->zoom *= this->zoom;
			this->zoom += 30;
			this->state = false;
		}
		else
		{
			this->zoom -= 30;
			this->state = true;
		}
		
	}
private:
	glm::vec3 position, front, up, right;  //位置，方向向量，上，右
	glm::vec3 worldUp;
	GLfloat yaw, pitch;		//俯仰角，偏航角
	GLfloat zoom;
	GLfloat speed, sensitivity;
	bool state = false;
	void updataCameraVectors()	//根据俯仰角和偏航角计算相机的方向向量等
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
		front.y = sin(glm::radians(this->pitch));
		front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));


		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp)); //叉乘
		this->up = glm::normalize(glm::cross(this->right, this->front));		//叉乘
	}
};