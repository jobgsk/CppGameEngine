#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "glm\gtc\matrix_transform.hpp"
//#include "glm\gtx\quaternion.hpp"
//#include "SOIL.h"
#include "bmp.h"
#include <functional>

class Graphics  {

	
public:

	static int winid;
	static GLuint program;

	//int BuffersMax = 100;
	//int TexturesMax = 100;

	//static GLuint * Buffers;
	//static GLuint * Textures;

	//static int BuffersCount;
	//static int TexturesCount;

	static GLuint location1;
	static GLuint location2;
	static GLuint location3;

	static GLuint location4;

	/*
		light 
	*/
	static GLuint location5;
	static GLuint location6;
	static GLuint location7;
	static GLuint location8;
	static GLuint location9;

	static glm::vec4 ambient_product;
	static glm::vec4 diffuse_product;
	static glm::vec4 specular_product;
	static glm::vec4 light_position;
	static float  material_shininess;


	Graphics(int myargc, char** myargv, const char *app_name);
	~Graphics();

	static void Display(std::function<void()> fun);
	static void Redispaly();

	static void Camera(float cx, float cy, float cz, float px, float py, float pz);
	static void Perspective();
	
	static void Reshape(int w, int h);
	static void EnableLight();
	static void DisableLight();
	static void EnableTexture();

	static void Run();
	static void Exit();
	

};

#endif /* GRAPHICS_H_ */