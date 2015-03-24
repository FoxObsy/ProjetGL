/* Include headers*//*{{{*/
#include <iostream>
#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <string.h>
#include <cstring>
#include <fstream>
#include "glfwMinimal.h"
/*}}}*/

GLuint vao,vbo,ibo, count, positionBuffer, indexBuffer, VertexShaderId, FragmentShaderId, ProgramId ;

int main(void)/*{{{*/
{

    std::cout << "Yes we can!!!" << std::endl;
	initGLFW();
	initGLEW();
	make_ressources();

	while(1){
		renderFrame();
	}
	
	cleanup();
	shutDown(0);
}/*}}}*/

// vim: ft=cpp foldmethod=marker:

void initGLFW() {
  if (!glfwInit()) shutDown(1);
  // Create OpenGL 4.4 Core Profile and Forward Compatible Context                                                   
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Create a window of given size
  const int window_width = 1024, window_height = 800;
  GLFWwindow* window =glfwCreateWindow(window_width, window_height,
        "Minimal OpenGL application with GLFW", NULL, NULL);
  if (!window) {
      std::cerr<<"Could not open a window"<<std::endl;
      shutDown(1);
  }
  // Make the context of the specified window current 
  glfwMakeContextCurrent(window);
}

void initGLEW()
{
    /* GLEW Initialization */
    // Do not forget to use glewExperimental so that glewInit works with core
    // profile: http://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        std::cerr<<"ERROR: "<< glewGetErrorString(GlewInitResult)<<std::endl;
        shutDown(1);
    }

}

// On visualise la Frame soit le triangle
void renderFrame(){
	glClear(GL_COLOR_BUFFER_BIT );
		
	glUseProgram(ProgramId);

	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
 // std::cout << "Avant dessin !!!" << std::endl;

 //glDrawArrays(GL_TRIANGLES, 0, 3*12);
  //glDrawElements(GL_TRIANGLES, 36,GL_FLOAT,0);

 //std::cout << "Après dessin !!!" << std::endl;
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
   glEnable(GL_CULL_FACE);
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT,0); 

	glBindVertexArray(0);
	glUseProgram(0);


	GLFWwindow* window = glfwGetCurrentContext();
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do {
  	glfwSwapBuffers(window);
    glfwPollEvents();
  }

  while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0 );
}


/**
* Fonction permettant la création du VBO ainsi que des buffers
*/
void CreateVBO(){
  /* TRIANGLE SIMPLE
	GLfloat positions[] = {
		-0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f,
		0.8f, -0.8f, 0.0f
	};*/


 /* ESSAI AVEC LES IBO */ 
  GLint positions[] = {
    -1, -1, -1, //1
    -1, -1, 1, //2
    1, -1, 1, //3
    1, -1, -1, //4
    -1, 1, -1, //5
    -1, 1, 1, //6
    1, 1, 1, //7
    1, 1, -1 //8
  };

  /* faire dans le même sens sinon kaput */
  GLint indices[] = {
    // 1er triangle
    6,
    7,
    2,
    // deuxième triangle
    2,
    3,
    0,
    // 3ème triangle
    0,
    4,
    7,
    // 4ème tirangle
    7,
    3,
    0,
    // 5ème triangle
    0,
    4,
    1,
    // 6ème
    1,
    5,
    4,
    // 7ème
    4,
    5,
    7,
    // 8ème
    7,
    6,
    5,
    // 9ème
    5,
    6,
    2,
    // 10ème
    2,
    5,
    1,
    // 11 ème
    1,
    0,
    2,
    // 12 ème
    2,
    7,
    3
  };

  
  // TRUC QUI MARCHE	
  /*  GLfloat positions[] = {
    -0.5f,-0.5f,-0.5f, // triangle 1 : begin
    -0.5f,-0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f, // triangle 1 : end
    0.5f, 0.5f,-0.5f, // triangle 2 : begin
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f,-0.5f, // triangle 2 : end
    0.5f,-0.5f, 0.5f,
    -0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f, 0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f,-0.5f,
    0.5f,-0.5f, 0.5f,
    -0.5f,-0.5f, 0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f,-0.5f, 0.5f,
    0.5f,-0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f, 0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f,-0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f,-0.5f,
    -0.5f, 0.5f,-0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f,-0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f,-0.5f, 0.5f
  };*/
	// Creation et activation du vao
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &positionBuffer);
	// On Bind le Buffer positionBuffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);

  /* IBO */
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
  GLint positionIndex = glGetAttribLocation(ProgramId, "position");

  /* Essai avec les IBO */
	glEnableVertexAttribArray(positionIndex);
	glVertexAttribPointer(positionIndex, 3, GL_INT, GL_FALSE, 0, 0);

  /* CAMERA ??!!?? */
  glm::mat4 Projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 View = glm::lookAt(glm::vec3(4,3,3),glm::vec3(0,0,0), glm::vec3(0,1,0));
  glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 mvp = Projection * View * Model;

  glUseProgram(ProgramId);
  GLint MatrixID = glGetUniformLocation(ProgramId, "mvp");
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
  glUseProgram(0);

  
 // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  count = sizeof(indices);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  /*FIN */
	glBindVertexArray(0);
  
 
   std::cout << "Je suis passé (crea + activation vao)" << std::endl;
};

/**
* Fonction permettant la Destruction des VBo précédement crée ainsi que des buffers de donnée
*/
void DestroyVBO(){
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &positionBuffer);
  glDeleteBuffers(1, &indexBuffer);

	glDeleteVertexArrays(1, &vao);
}

// Fonction permettant de sortir à tout moment du programme
void shutDown(int i){
  glfwTerminate();
	exit(i);
}

// On créer les ressources nécessaire pour le triangle soit les VBO et les shaders
void make_ressources(){
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  std::cout << "Avant shaders" << std::endl;

  CreateShaders();
  std::cout << "Je suis passé (après shaders)" << std::endl;
  CreateVBO();

  
}

// On nettoie tout 
void cleanup(){
  DestroyShaders();
  DestroyVBO();
}

// Création des shaders à partir des fichier source
void CreateShaders(){
	GLint vLength, fLength;
  /*
	std::string vS = file_contents("../minimal.v.glsl");
	std::string fS = file_contents("../minimal.f.glsl");
  */

  std::string vS = file_contents("../minimal.v.glsl");
  std::string fS = file_contents("../minimal.f.glsl");

  GLchar* vSource =(GLchar*)vS.c_str();
  GLchar* fSource =(GLchar*)fS.c_str();

  vLength = (GLint)vS.length();
  fLength = (GLint)fS.length();

	GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, (const GLchar**)&(vSource), &vLength);
	glCompileShader(VertexShaderId);

	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, (const GLchar**)&(fSource), &fLength);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
}

// Destruction des Shaders 
void DestroyShaders(){
	glUseProgram(0);
	
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(VertexShaderId);
	glDeleteShader(FragmentShaderId);

	glDeleteProgram(ProgramId);
}


//Lecture des fichiers shaders
std::string file_contents(char * fileName)
{
    std::ifstream infile(fileName);


    std::string result ="";
    std::string str="";
    while(std::getline(infile,str))
    {
        result = result + str +"\n";
    }
    return result;
}