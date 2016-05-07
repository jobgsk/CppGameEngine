#include <iostream>

#include "Graphics.h"

int Graphics::winid = 0;

GLuint Graphics::program = 0;

//GLuint * Graphics::Buffers;
//GLuint Graphics::Textures;

//int Graphics::BuffersCount = 0;
//int Graphics::TexturesCount = -1;

GLuint Graphics::location1 = 0;
GLuint Graphics::location2 = 0;
GLuint Graphics::location3 = 0;

GLuint Graphics::location4 = 0;

/*
	light
*/
GLuint Graphics::location5 = 0;
GLuint Graphics::location6 = 0;
GLuint Graphics::location7 = 0;
GLuint Graphics::location8 = 0;
GLuint Graphics::location9 = 0;

// Initialize shader lighting parameters
glm::vec4 Graphics::light_position = glm::vec4(25.0, 2.0, 25.0, 0.0);
float  Graphics::material_shininess = 100.0;

glm::vec4 light_ambient(0.2, 0.2, 0.2, 1.0);
glm::vec4 light_diffuse(1.0, 1.0, 1.0, 1.0);
glm::vec4 light_specular(1.0, 1.0, 1.0, 1.0);

glm::vec4 material_ambient(1.0, 0.0, 1.0, 1.0);
glm::vec4 material_diffuse(1.0, 0.8, 0.0, 1.0);
glm::vec4 material_specular(1.0, 0.8, 0.0, 1.0);

glm::vec4 Graphics::ambient_product = light_ambient * material_ambient;
glm::vec4 Graphics::diffuse_product = light_diffuse * material_diffuse;
glm::vec4 Graphics::specular_product = light_specular * material_specular;



//GLuint program;

//GLuint location_model_matrix;
//GLuint location_camera_matrix;
//GLuint location_projection_matrix;

//GLuint vertices_coord_buffer;
//GLuint collor_coord_buffer;
//GLuint texture_coord_buffer;
//GLuint normals_coord_buffer;

//GLuint Buffers[4];

//GLuint TextureBuffer;

//GLuint Texture[2];


Graphics::Graphics(int myargc, char** myargv, const char *app_name)
{

	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	Graphics::winid = glutCreateWindow(app_name);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewInit();	//Initializes the glew and prepares the drawing pipeline.


	//glGenTextures(100, Texture);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	Graphics::program = LoadShaders(shaders);
	glUseProgram(Graphics::program);	//My Pipeline is set up

	Graphics::location1 = glGetUniformLocation(program, "model_matrix");
	Graphics::location2 = glGetUniformLocation(program, "camera_matrix");
	Graphics::location3 = glGetUniformLocation(program, "projection_matrix");

	Graphics::location4 = glGetUniformLocation(program, "is_color");

	Graphics::location5 = glGetUniformLocation(program, "AmbientProduct");
	Graphics::location6 = glGetUniformLocation(program, "DiffuseProduct");
	Graphics::location7 = glGetUniformLocation(program, "SpecularProduct");
	Graphics::location8 = glGetUniformLocation(program, "LightPosition");
	Graphics::location9 = glGetUniformLocation(program, "Shininess");

	std::cout << " test 1  programm " << program << std::endl;
};


void Graphics::Reshape(int w, int h)
{

}

void Graphics::Camera(float cx, float cy, float cz, float px, float py, float pz)
{
	glm::vec3 pos = glm::vec3(cx, cy, cz);
	glm::vec3 look = glm::vec3(px, py, pz);

	
	//float camera_distance = 5.0;
	glm::mat4 camera_matrix = glm::lookAt(
		pos, //glm::vec3(0.0, 0.0, camera_distance),	// Camera position
		look, //glm::vec3(0.0, 0.0, -1.0),				// Look at point
		glm::vec3(0.0, 1.0, 0.0));				// Up vector
	glUniformMatrix4fv(Graphics::location2, 1, GL_FALSE, &camera_matrix[0][0]);
}


void Graphics::Perspective()
{
	glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);
	glUniformMatrix4fv(Graphics::location3, 1, GL_FALSE, &projection_matrix[0][0]);
};

void Graphics::Display(std::function<void()> dispaly)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*
	light
	*/
	glUniform4fv(Graphics::location5, 1, &ambient_product[0]);
	glUniform4fv(Graphics::location6, 1, &diffuse_product[0]);
	glUniform4fv(Graphics::location7, 1, &specular_product[0]);
	glUniform4fv(Graphics::location8, 1, &light_position[0]);
	glUniform1f(Graphics::location9, material_shininess);
	//glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	//glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	//glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	//glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	//glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

	/*
		model view
	*/
	glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
	glUniformMatrix4fv(Graphics::location1, 1, GL_FALSE, &model_view[0][0]);

	//std::cout << " test 2  Texture " << Texture[1] << " Buffers " << Buffers[0]<< std::endl;

	dispaly();

	glFlush();
}

void Graphics::Redispaly()
{
	glutPostRedisplay();
}

void Graphics::EnableTexture()
{

}

void Graphics::EnableLight()
{

}

void Graphics::DisableLight()
{

}

void Graphics::Run()
{
	glutMainLoop();
}

void Graphics::Exit()
{
	glutDestroyWindow(Graphics::winid);
}

Graphics::~Graphics()
{
	Exit();
}