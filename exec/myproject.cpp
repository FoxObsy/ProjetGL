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

//#include <AntTweakBar.h>

#include "utils/textures.h"
#include "utils/controls.h"
#include "utils/objloader.h"

#include "include/GameState.hpp"
#include "include/Tile.hpp"

#define WIDTH 1024
#define HEIGHT 768
#define PI glm::pi<float>()

GLFWwindow* window;
std::string lvl = "1";

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

void updateMatrix(glm::vec3* translations, GameState gameState, int nb){
  Matrix map = gameState.getMatrix();
  int nbBoxes = 0;
  float offset = 0.1f;
  for(int x=0; x<map.getRow(); x++){
    for(int z=0; z<map.getColumn(); z++){
      if(map.getMatrix()[x][z].hasBox()){
	glm::vec3 translation;
	translation.y = 0.0f;
	translation.x = -(float)x + offset;
	translation.z = (float)z + offset;
	translations[nbBoxes++] = translation;
      }
    }
  }
}

/******************************************************************************/

int main(void)
{
  /*********************** Initialisation **************************/

  if (!glfwInit()) return -1; //shutDown(1);

  // Create OpenGL 4.4 Core Profile and Forward Compatible Context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
  /*
  TwInit(TW_OPENGL_CORE, NULL);
  TwWindowSize(WIDTH, HEIGHT);
  TwBar * GUI = TwNewBar("HUD");
  TwSetParam(GUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
  TwDefine(" ViewMatrix size='400 200' valueswidth=fit ");
  double hudTime;
  int hudMoves = 0;
  TwAddVarRW(GUI, "Nombre de coups", TW_TYPE_INT8, &hudMoves, NULL);
  TwAddVarRW(GUI, "Temps", TW_TYPE_DOUBLE, &hudTime, NULL);
  */
  int hudMoves = 0;


  /**************** Bloc ********************/
  GLuint programIDBloc = shader_loader("../resources/lvl"+lvl+"/shaderbloc"+lvl+".v.glsl","../resources/lvl"+lvl+"/shaderbloc"+lvl+".f.glsl");
  
  GLuint vaoBloc;
  glGenVertexArrays(1, &vaoBloc);
  glBindVertexArray(vaoBloc);
  //---------CPU side version
  std::vector<glm::vec3> positionsBloc;
  std::vector<glm::vec2> uvsBloc;
  std::vector<glm::vec3> normalsBloc;
  loadOBJ(("../resources/lvl"+lvl+"/bloc"+lvl+".obj").c_str(),positionsBloc,uvsBloc,normalsBloc);

  GLuint textureBloc = loadTGATexture("../resources/lvl"+lvl+"/bloc"+lvl+"_diffus.tga");
  GLuint textureBlocID = glGetUniformLocation(programIDBloc, "colorMap");

  //---------GPU side version
  GLuint positionBlocBuffer;
  glGenBuffers(1, &positionBlocBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBlocBuffer);
  glBufferData(GL_ARRAY_BUFFER, positionsBloc.size()*sizeof(glm::vec3), &positionsBloc[0], GL_STATIC_DRAW);
  GLint positionBlocIndex = glGetAttribLocation(programIDBloc, "position");
  glEnableVertexAttribArray(positionBlocIndex);
  glVertexAttribPointer(positionBlocIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionBlocIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint uvBlocBuffer;
  glGenBuffers(1, &uvBlocBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvBlocBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvsBloc.size()*sizeof(glm::vec2), &uvsBloc[0], GL_STATIC_DRAW);
  GLint uvBlocIndex = glGetAttribLocation(programIDBloc, "uv");
  glEnableVertexAttribArray(uvBlocIndex);
  glVertexAttribPointer(uvBlocIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(uvBlocIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);


  /**************** Robot ********************/
  GLuint programIDRobot = shader_loader("../resources/soko/shaderSoko.v.glsl","../resources/soko/shaderSoko.f.glsl");

  GLuint vaoRobot;
  glGenVertexArrays(1, &vaoRobot);
  glBindVertexArray(vaoRobot);
  //---------CPU side version
  std::vector<glm::vec3> positionsRobot;
  std::vector<glm::vec2> uvsRobot;
  std::vector<glm::vec3> normalsRobot;
  loadOBJ("../resources/soko/soko.obj",positionsRobot,uvsRobot,normalsRobot);

  GLuint textureRobot = loadTGATexture("../resources/soko/diffus_robot.tga");
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


  /**************** Level ********************/
  GLuint programIDLvl = shader_loader("../resources/lvl"+lvl+"/shaderlvl"+lvl+".v.glsl","../resources/lvl"+lvl+"/shaderlvl"+lvl+".f.glsl");

  GLuint vaoLvl;
  glGenVertexArrays(1, &vaoLvl);
  glBindVertexArray(vaoLvl);
  //---------CPU side version
  std::vector<glm::vec3> positionsLvl;
  std::vector<glm::vec2> uvsLvl;
  std::vector<glm::vec3> normalsLvl;
  loadOBJ(("../resources/lvl"+lvl+"/lvl"+lvl+".obj").c_str(),positionsLvl,uvsLvl,normalsLvl);

  GLuint textureLvl = loadTGATexture("../resources/lvl"+lvl+"/lvl"+lvl+"_diffus.tga");
  GLuint textureLvlID = glGetUniformLocation(programIDLvl, "colorMap");

  //---------GPU side version
  GLuint positionLvlBuffer;
  glGenBuffers(1, &positionLvlBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionLvlBuffer);
  glBufferData(GL_ARRAY_BUFFER, positionsLvl.size()*sizeof(glm::vec3), &positionsLvl[0], GL_STATIC_DRAW);
  GLint positionLvlIndex = glGetAttribLocation(programIDLvl, "position");
  glEnableVertexAttribArray(positionLvlIndex);
  glVertexAttribPointer(positionLvlIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionLvlIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint uvLvlBuffer;
  glGenBuffers(1, &uvLvlBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvLvlBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvsLvl.size()*sizeof(glm::vec2), &uvsLvl[0], GL_STATIC_DRAW);
  GLint uvLvlIndex = glGetAttribLocation(programIDLvl, "uv");
  glEnableVertexAttribArray(uvLvlIndex);
  glVertexAttribPointer(uvLvlIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(uvLvlIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  
  /***************** Test Matrice *****************/
  
  GameState gameState("../resources/lvl"+lvl+"/lvl"+lvl+".txt");
  Matrix map = gameState.getMatrix();
  int mapRow = map.getRow();
  int mapColumn = map.getColumn();
  std::cout << mapRow << " - " << mapColumn << std::endl;
  glm::vec3 translations[/*mapRow * mapColumn*/70];
  int nbBoxes = 0;
  float offset = 0.1f;
  for(int x=0; x<mapRow; x++){
    for(int z=0; z<mapColumn; z++){
      if(map.getMatrix()[x][z].hasBox()){
	glm::vec3 translation;
	translation.y = 0.0f;
	translation.x = -(float)x + offset;
	translation.z = (float)z + offset;
	translations[nbBoxes++] = translation;
      }
    }
  }

  /**********************************************************/

  GLuint MatrixIDBloc = glGetUniformLocation(programIDBloc, "MVP");
  GLuint MatrixIDRobot = glGetUniformLocation(programIDRobot, "MVP");
  
  glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 ViewMatrix;
  glm::mat4 ModelMatrixBloc = glm::translate(glm::mat4(1.0),glm::vec3(0.0f,-0.8f,0.0f));
  glm::mat4 ModelMatrixRobot = glm::translate(glm::mat4(1.0),glm::vec3(0.0f,-0.7f,0.5f));
  //offset robot -> z+0.5f
  glm::mat4 MVPBloc;
  glm::mat4 MVPRobot;


  /*********************** Boucle **************************/

  while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){

    //hudTime = glfwGetTime();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ViewMatrix = computeMatricesFromInputs(window);
    /*
    if(mouse click){

    }
    */

    /****Robot****/
    glUseProgram(programIDRobot);

    ModelMatrixRobot = moveRobot(window, gameState, ModelMatrixRobot, hudMoves);
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
    glBindVertexArray(0);


    /****Level****/
    glUseProgram(programIDLvl);

    MVPBloc = ProjectionMatrix * ViewMatrix * ModelMatrixBloc;
    glUniformMatrix4fv(MatrixIDBloc, 1, GL_FALSE, &MVPBloc[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureLvl);
    glUniform1i(textureLvlID, 0);

    glBindVertexArray(vaoLvl);
    glEnableVertexAttribArray(positionLvlIndex);
    glEnableVertexAttribArray(uvLvlIndex);

    glDrawArrays(GL_TRIANGLES, 0, positionsLvl.size());

    glDisableVertexAttribArray(positionLvlIndex);
    glDisableVertexAttribArray(uvLvlIndex);
    glBindVertexArray(0);


    /****Bloc****/
    glUseProgram(0);
    glUseProgram(programIDBloc);

    MVPBloc = ProjectionMatrix * ViewMatrix * ModelMatrixBloc;
    glUniformMatrix4fv(MatrixIDBloc, 1, GL_FALSE, &MVPBloc[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBloc);
    glUniform1i(textureBlocID, 0);

    //updateMatrix(translations, gameState, nbBoxes);
    for(int i=0; i<nbBoxes; i++){
      std::stringstream ss;
      std::string index;
      ss << i; 
      index = ss.str(); 
      GLuint translID = glGetUniformLocation(programIDBloc, ("transl[" + index + "]").c_str());
      glUniform3f(translID, translations[i].x, translations[i].y, translations[i].z);
    }

    glBindVertexArray(vaoBloc);
    glEnableVertexAttribArray(positionBlocIndex);
    glEnableVertexAttribArray(uvBlocIndex);

    glDrawArraysInstanced(GL_TRIANGLES, 0, positionsBloc.size(), nbBoxes);

    glDisableVertexAttribArray(positionBlocIndex);
    glDisableVertexAttribArray(uvBlocIndex);

    /*************/
    glfwSwapBuffers(window);
    glfwPollEvents();

    glBindVertexArray(0);
    glUseProgram(0);
  }


  /*********************** Nettoyage **************************/

  glDeleteBuffers(1, &positionBlocBuffer);
  glDeleteBuffers(1, &positionRobotBuffer);
  glDeleteBuffers(1, &positionLvlBuffer);
  glDeleteBuffers(1, &uvBlocBuffer);
  glDeleteBuffers(1, &uvRobotBuffer);
  glDeleteBuffers(1, &uvLvlBuffer);
  glDeleteVertexArrays(1, &vaoRobot);
  glDeleteVertexArrays(1, &vaoBloc);
  glDeleteVertexArrays(1, &vaoLvl);
  glDeleteProgram(programIDBloc);
  glDeleteProgram(programIDRobot);
  glDeleteProgram(programIDLvl);

  glfwTerminate();

  return 0; //shutDown(0);

}

