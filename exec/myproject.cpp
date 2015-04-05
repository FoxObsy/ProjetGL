/* Include headers*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "utils/textures.h"
#include "utils/controls.h"
#include "utils/objloader.h"

#define WIDTH 1024
#define HEIGHT 768
#define PI glm::pi<float>()

char keyOnce2[GLFW_KEY_LAST + 1];
#define glfwGetKeyOnce2(WINDOW, KEY)             \
    (glfwGetKey(WINDOW, KEY) ?              \
     (keyOnce2[KEY] ? false : (keyOnce2[KEY] = true)) :   \
     (keyOnce2[KEY] = false))

GLFWwindow* window;

char* file_contents(std::string name, GLint* l){
  std::string code;
  std::ifstream fStream(name, std::ios::in);
  if(fStream.is_open()){
    std::string line = "";
    while(getline(fStream, line))
      code += "\n" + line;
    fStream.close();
    *l = (GLint) code.length();
    char* charCode = new char[code.length()+1];
    strcpy(charCode, code.c_str());
    return charCode;
  }else{
    printf("Impossible to open\n");
    getchar();
    return 0;
  }
}

GLuint shader_loader(std::string vertex, std::string fragment){
  //---- CPU side for shader program
  GLint vLength, fLength;
  GLchar *vSource = (GLchar*)file_contents(vertex, &vLength);
  GLchar *fSource = (GLchar*)file_contents(fragment, &fLength);
  //---- GPU side (Load and compile)
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShader, 1, (const GLchar**)&vSource, &vLength);
  glCompileShader(vShader);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);   
  glShaderSource(fShader, 1, (const GLchar**)&fSource, &fLength);
  glCompileShader(fShader);
  //---- gpu side (link)
  GLuint programid = glCreateProgram();
  glAttachShader(programid, vShader);
  glAttachShader(programid, fShader);
  glLinkProgram(programid);
  return programid;
}

/********************************************************************************/

int main(void)
{
  /*********************** Initialisation **************************/

  if (!glfwInit()) return -1; //shutDown(1);

  // Create OpenGL 4.4 Core Profile and Forward Compatible Context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window of given size
  window =glfwCreateWindow(WIDTH, HEIGHT, "Minimal OpenGL application with GLFW", NULL, NULL);

  if (!window) {
    std::cerr<<"Could not open a window"<<std::endl;
    return -1; //shutDown(1);
  }

  // Make the context of the specified window current 
  glfwMakeContextCurrent(window);

  /* GLEW Initialization */
  glewExperimental = GL_TRUE;
  GLenum GlewInitResult = glewInit();
  if (GlewInitResult != GLEW_OK) {
    std::cerr<<"ERROR: "<< glewGetErrorString(GlewInitResult)<<std::endl;
    return -1; //shutDown(1);
  }
  
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  glClearColor(0.3, 0.3, 0.0, 0.0);


  /**************** Plan ********************/
  GLuint programIDPlan = shader_loader("shaderPlan.v.glsl","shaderPlan.f.glsl");
  
  GLuint vaoPlan;
  glGenVertexArrays(1, &vaoPlan);
  glBindVertexArray(vaoPlan);
  //---------CPU side version
  float positionsPlan[]={0,0,0, 0,0,1, 1,0,0,   1,0,0, 0,0,1, 1,0,1};
  GLuint vertexCountPlan = 6;
  
  GLuint texturePlan = loadTGATexture("brick_colormap.tga");
  GLuint texturePlanID = glGetUniformLocation(programIDPlan, "colorMap");

  std::vector<glm::vec2> uvsPlan={
        glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,0),
        glm::vec2(1,0),  glm::vec2(0,1), glm::vec2(1,1)
  };

  //---------GPU side version
  GLuint positionPlanBuffer;
  glGenBuffers(1, &positionPlanBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionPlanBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertexCountPlan* 3 * sizeof(float), positionsPlan, GL_STATIC_DRAW);
  GLint positionPlanIndex = glGetAttribLocation(programIDPlan, "position");
  glEnableVertexAttribArray(positionPlanIndex);
  glVertexAttribPointer(positionPlanIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionPlanIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint uvPlanBuffer;
  glGenBuffers(1, &uvPlanBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvPlanBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvsPlan.size()*sizeof(glm::vec2), &uvsPlan[0], GL_STATIC_DRAW);
  GLint uvPlanIndex = glGetAttribLocation(programIDPlan, "uv");
  glEnableVertexAttribArray(uvPlanIndex);
  glVertexAttribPointer(uvPlanIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(uvPlanIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);


  /**************** Robot ********************/
  GLuint programIDRobot = shader_loader("shaderRobot.v.glsl","shaderRobot.f.glsl");

  GLuint vaoRobot;
  glGenVertexArrays(1, &vaoRobot);
  glBindVertexArray(vaoRobot);
  //---------CPU side version
  std::vector<glm::vec3> positionsRobot;
  std::vector<glm::vec2> uvsRobot;
  std::vector<glm::vec3> normalsRobot;
  loadOBJ("soko_fromBlender.obj",positionsRobot,uvsRobot,normalsRobot);

  GLuint textureRobot = loadTGATexture("diffus_robot.tga");
  GLuint textureRobotID = glGetUniformLocation(programIDRobot, "colorMap");

  //---------GPU side version
  GLuint positionRobotBuffer;
  glGenBuffers(1, &positionRobotBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionRobotBuffer);
  glBufferData(GL_ARRAY_BUFFER, positionsRobot.size()*sizeof(glm::vec3), &positionsRobot[0], GL_STATIC_DRAW);
  GLint positionRobotIndex = glGetAttribLocation(programIDRobot, "position");
  glEnableVertexAttribArray(positionRobotIndex);
  glVertexAttribPointer(positionRobotIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionRobotIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint uvRobotBuffer;
  glGenBuffers(1, &uvRobotBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvRobotBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvsRobot.size()*sizeof(glm::vec2), &uvsRobot[0], GL_STATIC_DRAW);
  GLint uvRobotIndex = glGetAttribLocation(programIDRobot, "uv");
  glEnableVertexAttribArray(uvRobotIndex);
  glVertexAttribPointer(uvRobotIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(uvRobotIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  
  /***************** Test Matrice *****************/

  int brique[5][5] = {{1,1,1,1,1},
		      {1,0,0,0,1},
		      {1,0,1,0,1},
		      {1,0,0,0,1},
		      {1,1,1,1,1}};
  glm::vec3 translations[25];
  int brique2[5][5] = {{1,0,0,0,1},
		       {0,1,0,1,0},
		       {0,0,1,0,0},
		       {0,1,0,1,0},
		       {1,0,0,0,1}};
  glm::vec3 translations2[25];
  int nbBrique1 = 0;
  int nbBrique2 = 0;
  float offset = 0.1f;
  for(int x=0; x<5; x+=1){
    for(int z=0; z<5; z+=1){
      if(brique[x][z]){
	glm::vec3 translation;
	translation.y = 0.0f;
	translation.x = -(float)x + offset;
	translation.z = (float)z + offset;
	translations[nbBrique1++] = translation;
      }
      if(brique2[x][z]){
	glm::vec3 translation;
	translation.y = 0.0f;
	translation.x = -(float)x + offset;
	translation.z = (float)z + offset;
	translations2[nbBrique2++] = translation;
      }
    }
  }
  int choiceMatrix = 1;
  int nbBrique = nbBrique1;

  /**********************************************************/

  GLuint MatrixIDPlan = glGetUniformLocation(programIDPlan, "MVP");
  GLuint MatrixIDRobot = glGetUniformLocation(programIDRobot, "MVP");
  
  glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 ViewMatrix;
  glm::mat4 ModelMatrixPlan = glm::translate(glm::mat4(1.0),glm::vec3(0.0f,-3.0f,0.0f));
  glm::mat4 ModelMatrixRobot = glm::mat4(1.0f);
  glm::mat4 MVPPlan;
  glm::mat4 MVPRobot;

  /*********************** Boucle **************************/

  while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ViewMatrix = computeMatricesFromInputs(window);

    /****Plan****/
    glUseProgram(programIDPlan);

    MVPPlan = ProjectionMatrix * ViewMatrix * ModelMatrixPlan;
    glUniformMatrix4fv(MatrixIDPlan, 1, GL_FALSE, &MVPPlan[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePlan);
    glUniform1i(texturePlanID, 0);

    //Update
    if(glfwGetKeyOnce2(window, GLFW_KEY_SPACE) == GLFW_PRESS){
      if(choiceMatrix==1){
	choiceMatrix=2;
      }
      else{
	choiceMatrix=1;
      }
    }
    if(choiceMatrix==1){
      for(int i=0; i<nbBrique1; i++){
	std::stringstream ss;
	std::string index;
	ss << i; 
	index = ss.str(); 
	GLuint translID = glGetUniformLocation(programIDPlan, ("transl[" + index + "]").c_str());
	glUniform3f(translID, translations[i].x, translations[i].y, translations[i].z);
      }
      nbBrique = nbBrique1;
    }
    else{
      for(int i=0; i<nbBrique2; i++){
	std::stringstream ss;
	std::string index;
	ss << i; 
	index = ss.str(); 
	GLuint translID = glGetUniformLocation(programIDPlan, ("transl[" + index + "]").c_str());
	glUniform3f(translID, translations2[i].x, translations2[i].y, translations2[i].z);
      }
      nbBrique = nbBrique2;
    }

    glBindVertexArray(vaoPlan);
    glEnableVertexAttribArray(positionPlanIndex);
    glEnableVertexAttribArray(uvPlanIndex);

    glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCountPlan, nbBrique);

    glDisableVertexAttribArray(positionPlanIndex);
    glDisableVertexAttribArray(uvPlanIndex);
    glBindVertexArray(0);


    /****Robot****/
    glUseProgram(0);
    glUseProgram(programIDRobot);

    ModelMatrixRobot = moveRobot(window, ModelMatrixRobot);
    MVPRobot = ProjectionMatrix * ViewMatrix * ModelMatrixRobot;
    glUniformMatrix4fv(MatrixIDRobot, 1, GL_FALSE, &MVPRobot[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureRobot);
    glUniform1i(textureRobotID, 0);

    glBindVertexArray(vaoRobot);
    glEnableVertexAttribArray(positionRobotIndex);
    glEnableVertexAttribArray(uvRobotIndex);

    glDrawArrays(GL_TRIANGLES, 0, positionsRobot.size());

    glDisableVertexAttribArray(positionRobotIndex);
    glDisableVertexAttribArray(uvRobotIndex);

    /*************/
    glfwSwapBuffers(window);
    glfwPollEvents();

    glBindVertexArray(0);
    glUseProgram(0);
  }


  /*********************** Nettoyage **************************/

  glDeleteBuffers(1, &positionPlanBuffer);
  glDeleteBuffers(1, &positionRobotBuffer);
  glDeleteBuffers(1, &uvPlanBuffer);
  glDeleteBuffers(1, &uvRobotBuffer);
  glDeleteVertexArrays(1, &vaoRobot);
  glDeleteVertexArrays(1, &vaoPlan);
  glDeleteProgram(programIDPlan);
  glDeleteProgram(programIDRobot);

  glfwTerminate();

  return 0; //shutDown(0);

}

