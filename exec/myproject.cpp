/* Include headers*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <irrKlang.h>

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

using namespace irrklang;

GLFWwindow* window;
//std::string lvl = "3";

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

void updateMatrix(glm::vec3* translations, int* targetBoxes, GameState gameState, int nb){
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
	translations[nbBoxes] = translation;
	if(map.getMatrix()[x][z].hasTarget()){
	  targetBoxes[nbBoxes] = 1;
	}
	else{
	  targetBoxes[nbBoxes] = 0;
	}
	nbBoxes++;
      }
    }
  }
}

/******************************************************************************/

int main(void)
{
  /*********************** Initialisation **************************/
  std::string lvl;
  int lvlID = 1;

  while(lvlID != 0){

    std::cout << "Choix du niveau (1,2,3, 0 pour quitter) : ";
    scanf("%d",&lvlID);
    if(lvlID == 0){
      return 0;
    }
    else{
      if(lvlID < 1 || lvlID > 3){
	lvl = "1";
	std::cout << "Niveau 1 choisi par défaut !" << std::endl;
      }
      else{
	lvl = std::to_string(lvlID);
      }
    }

    ISoundEngine* engine = createIrrKlangDevice();
    ISoundSource* caisse = engine->addSoundSourceFromFile("../resources/sound/boxSound.ogg");
    ISoundSource* pas = engine->addSoundSourceFromFile("../resources/sound/Pas.ogg"); 
    ISoundSource* just = engine->addSoundSourceFromFile("../resources/sound/just.ogg");
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
    GLuint lightcolorBlocID = glGetUniformLocation(programIDBloc, "lightcolor");

    //---------GPU side version
    GLuint positionBlocBuffer;
    glGenBuffers(1, &positionBlocBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBlocBuffer);
    glBufferData(GL_ARRAY_BUFFER, positionsBloc.size()*sizeof(glm::vec3), &positionsBloc[0], GL_STATIC_DRAW);
    GLint positionBlocIndex = glGetAttribLocation(programIDBloc, "vert_position");
    glEnableVertexAttribArray(positionBlocIndex);
    glVertexAttribPointer(positionBlocIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(positionBlocIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uvBlocBuffer;
    glGenBuffers(1, &uvBlocBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBlocBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvsBloc.size()*sizeof(glm::vec2), &uvsBloc[0], GL_STATIC_DRAW);
    GLint uvBlocIndex = glGetAttribLocation(programIDBloc, "vert_uv");
    glEnableVertexAttribArray(uvBlocIndex);
    glVertexAttribPointer(uvBlocIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(uvBlocIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalBlocBuffer;
    glGenBuffers(1, &normalBlocBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBlocBuffer);
    glBufferData(GL_ARRAY_BUFFER, normalsBloc.size()*sizeof(glm::vec3), &normalsBloc[0], GL_STATIC_DRAW);
    GLint normalBlocIndex = glGetAttribLocation(programIDBloc, "vert_normal");
    glEnableVertexAttribArray(normalBlocIndex);
    glVertexAttribPointer(normalBlocIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(normalBlocIndex);
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
    //GLuint lightdirnRobotID = glGetUniformLocation(programIDRobot, "lightdirn");
    GLuint lightcolorRobotID = glGetUniformLocation(programIDRobot, "lightcolor");

    //---------GPU side version
    GLuint positionRobotBuffer;
    glGenBuffers(1, &positionRobotBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionRobotBuffer);
    glBufferData(GL_ARRAY_BUFFER, positionsRobot.size()*sizeof(glm::vec3), &positionsRobot[0], GL_STATIC_DRAW);
    GLint positionRobotIndex = glGetAttribLocation(programIDRobot, "vert_position");
    glEnableVertexAttribArray(positionRobotIndex);
    glVertexAttribPointer(positionRobotIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(positionRobotIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uvRobotBuffer;
    glGenBuffers(1, &uvRobotBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvRobotBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvsRobot.size()*sizeof(glm::vec2), &uvsRobot[0], GL_STATIC_DRAW);
    GLint uvRobotIndex = glGetAttribLocation(programIDRobot, "vert_uv");
    glEnableVertexAttribArray(uvRobotIndex);
    glVertexAttribPointer(uvRobotIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(uvRobotIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalRobotBuffer;
    glGenBuffers(1, &normalRobotBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalRobotBuffer);
    glBufferData(GL_ARRAY_BUFFER, normalsRobot.size()*sizeof(glm::vec3), &normalsRobot[0], GL_STATIC_DRAW);
    GLint normalRobotIndex = glGetAttribLocation(programIDRobot, "vert_normal");
    glEnableVertexAttribArray(normalRobotIndex);
    glVertexAttribPointer(normalRobotIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(normalRobotIndex);
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
    GLuint lightcolorLvlID = glGetUniformLocation(programIDLvl, "lightcolor");

    //---------GPU side version
    GLuint positionLvlBuffer;
    glGenBuffers(1, &positionLvlBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionLvlBuffer);
    glBufferData(GL_ARRAY_BUFFER, positionsLvl.size()*sizeof(glm::vec3), &positionsLvl[0], GL_STATIC_DRAW);
    GLint positionLvlIndex = glGetAttribLocation(programIDLvl, "vert_position");
    glEnableVertexAttribArray(positionLvlIndex);
    glVertexAttribPointer(positionLvlIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(positionLvlIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uvLvlBuffer;
    glGenBuffers(1, &uvLvlBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvLvlBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvsLvl.size()*sizeof(glm::vec2), &uvsLvl[0], GL_STATIC_DRAW);
    GLint uvLvlIndex = glGetAttribLocation(programIDLvl, "vert_uv");
    glEnableVertexAttribArray(uvLvlIndex);
    glVertexAttribPointer(uvLvlIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(uvLvlIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalLvlBuffer;
    glGenBuffers(1, &normalLvlBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalLvlBuffer);
    glBufferData(GL_ARRAY_BUFFER, normalsLvl.size()*sizeof(glm::vec3), &normalsLvl[0], GL_STATIC_DRAW);
    GLint normalLvlIndex = glGetAttribLocation(programIDLvl, "vert_normal");
    glEnableVertexAttribArray(normalLvlIndex);
    glVertexAttribPointer(normalLvlIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(normalLvlIndex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
  
    /***************** Test Matrice *****************/
  
    GameState gameState("../resources/lvl"+lvl+"/lvl"+lvl+".txt");
    Matrix map = gameState.getMatrix();
    int mapRow = map.getRow();
    int mapColumn = map.getColumn();
    //glm::vec3 *translations = new glm::vec3[mapRow * mapColumn];
    /***** MUSIC *****/
    ISoundSource* music;
    string sMusic = "../resources/sound/sound"+lvl+".ogg";
    music = engine->addSoundSourceFromFile(sMusic.c_str()); 
    music->setDefaultVolume(0.3f);
    engine->play2D(music, true);

    /*****************/
    glm::vec3 translations[25];
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
    //int *targetBoxes = new int[nbBoxes];
    int targetBoxes[25];
    for(int i=0; i<nbBoxes; i++){
      targetBoxes[i] = 0;
    }

    /**********************************************************/
    initParameters();

    GLuint MatrixIDBloc = glGetUniformLocation(programIDBloc, "MVP");
    GLuint MatrixIDLvl = glGetUniformLocation(programIDLvl, "MVP");
    GLuint MatrixIDRobot = glGetUniformLocation(programIDRobot, "MVP");
    GLuint ViewIDRobot = glGetUniformLocation(programIDRobot, "V");
    GLuint ModelIDRobot = glGetUniformLocation(programIDRobot, "M");
    GLuint LightIDRobot = glGetUniformLocation(programIDRobot, "LightPosition");
    GLuint ViewIDLvl = glGetUniformLocation(programIDLvl, "V");
    GLuint ModelIDLvl = glGetUniformLocation(programIDLvl, "M");
    GLuint LightIDLvl = glGetUniformLocation(programIDLvl, "LightPosition");
    GLuint ViewIDBloc = glGetUniformLocation(programIDBloc, "V");
    GLuint ModelIDBloc = glGetUniformLocation(programIDBloc, "M");
    GLuint LightIDBloc = glGetUniformLocation(programIDBloc, "LightPosition");
  
    glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 ViewMatrix;
    glm::mat4 ModelMatrixBloc;
    glm::mat4 ModelMatrixLvl;
    glm::mat4 ModelMatrixRobot;
  
    if(lvl=="1"){
      glClearColor(216/255.0, 216/255.0, 1.0, 0.0);
      ModelMatrixBloc = glm::translate(glm::mat4(1.0),glm::vec3(4.5f,0.1f,-3.0f));
      ModelMatrixLvl = glm::rotate(glm::mat4(1.0),-PI/2,glm::vec3(0.0f,1.0f,0.0f));
      ModelMatrixRobot = glm::translate(glm::mat4(1.0),glm::vec3(3.5f,0.1f,0.0f));
    }
    else if(lvl=="2"){
      glClearColor(1.0, 186/255.0, 237/255.0, 0.0);
      ModelMatrixBloc = glm::translate(glm::mat4(1.0),glm::vec3(4.9f,0.0f,-4.7f));
      ModelMatrixLvl = glm::rotate(glm::mat4(1.0),-PI/2,glm::vec3(0.0f,1.0f,0.0f));
      ModelMatrixRobot = glm::translate(glm::mat4(1.0),glm::vec3(0.0f,0.0f,-0.5f));
    }
    else{
      glClearColor(0.69, 1.0, 1.0, 0.0);
      ModelMatrixBloc = glm::translate(glm::mat4(1.0),glm::vec3(3.3f,0.1f,-3.7f));
      ModelMatrixLvl = glm::rotate(glm::mat4(1.0),PI/2,glm::vec3(0.0f,1.0f,0.0f));
      ModelMatrixLvl = glm::scale(ModelMatrixLvl,glm::vec3(1.15f,1.15f,1.15f));
      ModelMatrixRobot = glm::translate(glm::mat4(1.0),glm::vec3(1.3f,0.1f,-0.6f));
    }
    //offset lvl1 : robot -> x+3.5f y+0.1f z+0.0f                                                   bloc  -> x+5.5f y+0.1f z-3.0f 
    //offset lvl2 : robot -> x+0.0f y+0.0f z-0.5f                                                   bloc  -> x+4.9f y+0.0f z-4.7f 
    //offset lvl3 : robot -> x+1.3f y+0.1f z-0.6f                                                   bloc  -> x+3.3f y+0.1f z-3.7f   lvl -> PI/2 scale1.15
    glm::mat4 MVPBloc;
    glm::mat4 MVPLvl;
    glm::mat4 MVPRobot;

    //GLuint textureEasterEgg = loadTGATexture("../resources/lvl"+lvl+"/bloc"+lvl+"_diffus.tga");
    //GLuint textureEasterEggID = glGetUniformLocation(programIDBloc, "colorMap");

    /*********************** Boucle **************************/

    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){

      //hudTime = glfwGetTime();

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ViewMatrix = computeMatricesFromInputs(window);

      glm::vec3 lightPos = glm::vec3(2,2,-2);

      /****Robot****/
      glUseProgram(programIDRobot);
      //glUniform3f(lightdirnRobotID,1.0f/1.415,0,1.0f/1.415);
      glUniform3f(lightcolorRobotID,0.7f,0.7f,204.0/255);

      ModelMatrixRobot = moveRobot(window, gameState, ModelMatrixRobot, hudMoves,engine,caisse,pas);
      updateMatrix(translations, targetBoxes, gameState, nbBoxes);
      MVPRobot = ProjectionMatrix * ViewMatrix * ModelMatrixRobot;

      glUniformMatrix4fv(MatrixIDRobot, 1, GL_FALSE, &MVPRobot[0][0]);
      glUniformMatrix4fv(ModelIDRobot, 1, GL_FALSE, &ModelMatrixRobot[0][0]);
      glUniformMatrix4fv(ViewIDRobot, 1, GL_FALSE, &ViewMatrix[0][0]);
      glUniform3f(LightIDRobot, lightPos.x, lightPos.y, lightPos.z);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textureRobot);
      glUniform1i(textureRobotID, 0);

      glBindVertexArray(vaoRobot);
      glEnableVertexAttribArray(positionRobotIndex);
      glEnableVertexAttribArray(uvRobotIndex);
      glEnableVertexAttribArray(normalRobotIndex);

      glDrawArrays(GL_TRIANGLES, 0, positionsRobot.size());

      glDisableVertexAttribArray(positionRobotIndex);
      glDisableVertexAttribArray(uvRobotIndex);
      glDisableVertexAttribArray(normalRobotIndex);
      glBindVertexArray(0);

      glUseProgram(0);

      /****Level****/
      glUseProgram(programIDLvl);
      glUniform3f(lightcolorLvlID,1.0f,1.0f,204.0/255);

      MVPLvl = ProjectionMatrix * ViewMatrix * ModelMatrixLvl;
      glUniformMatrix4fv(MatrixIDLvl, 1, GL_FALSE, &MVPLvl[0][0]);
      glUniformMatrix4fv(ModelIDLvl, 1, GL_FALSE, &ModelMatrixLvl[0][0]);
      glUniformMatrix4fv(ViewIDLvl, 1, GL_FALSE, &ViewMatrix[0][0]);
      glUniform3f(LightIDLvl, lightPos.x, lightPos.y, lightPos.z);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textureLvl);
      glUniform1i(textureLvlID, 0);

      glBindVertexArray(vaoLvl);
      glEnableVertexAttribArray(positionLvlIndex);
      glEnableVertexAttribArray(uvLvlIndex);
      glEnableVertexAttribArray(normalLvlIndex);

      glDrawArrays(GL_TRIANGLES, 0, positionsLvl.size());

      glDisableVertexAttribArray(positionLvlIndex);
      glDisableVertexAttribArray(uvLvlIndex);
      glDisableVertexAttribArray(normalLvlIndex);
      glBindVertexArray(0);

      glUseProgram(0);

      /****Bloc****/
      glUseProgram(programIDBloc);
      glUniform3f(lightcolorBlocID,1.0f,1.0f,204.0/255);

      MVPBloc = ProjectionMatrix * ViewMatrix * ModelMatrixBloc;
      glUniformMatrix4fv(MatrixIDBloc, 1, GL_FALSE, &MVPBloc[0][0]);
      glUniformMatrix4fv(ModelIDBloc, 1, GL_FALSE, &ModelMatrixBloc[0][0]);
      glUniformMatrix4fv(ViewIDBloc, 1, GL_FALSE, &ViewMatrix[0][0]);
      glUniform3f(LightIDBloc, lightPos.x, lightPos.y, lightPos.z);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textureBloc);
      glUniform1i(textureBlocID, 0);
      /*
	if(gameState.getEnd()){
	std::cout << "Félicitations, tu as gagné ! =)" << std::endl;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureEasterEgg);
	glUniform1i(textureEasterEggID, 0);
	}
	else{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureBloc);
	glUniform1i(textureBlocID, 0);
	}
      */
      for(int i=0; i<nbBoxes; i++){
	std::stringstream ss;
	std::string index;
	ss << i; 
	index = ss.str(); 
	GLuint translID = glGetUniformLocation(programIDBloc, ("transl[" + index + "]").c_str());
	glUniform3f(translID, translations[i].x, translations[i].y, translations[i].z);
	GLuint targetBoxID = glGetUniformLocation(programIDBloc, "target");
	glUniform1i(targetBoxID, targetBoxes[i]);
	//std::cout << targetBoxes[i] << std::endl;
      }

      glBindVertexArray(vaoBloc);
      glEnableVertexAttribArray(positionBlocIndex);
      glEnableVertexAttribArray(uvBlocIndex);
      glEnableVertexAttribArray(normalBlocIndex);

      glDrawArraysInstanced(GL_TRIANGLES, 0, positionsBloc.size(), nbBoxes);

      glDisableVertexAttribArray(positionBlocIndex);
      glDisableVertexAttribArray(uvBlocIndex);
      glDisableVertexAttribArray(normalBlocIndex);

      /*************/
      glfwSwapBuffers(window);
      glfwPollEvents();

      glBindVertexArray(0);
      glUseProgram(0);
      
      if(gameState.getEnd()){
	engine->play2D(just,false);
      }
    }


    /*********************** Nettoyage **************************/

    glDeleteBuffers(1, &positionBlocBuffer);
    glDeleteBuffers(1, &positionRobotBuffer);
    glDeleteBuffers(1, &positionLvlBuffer);
    glDeleteBuffers(1, &uvBlocBuffer);
    glDeleteBuffers(1, &uvRobotBuffer);
    glDeleteBuffers(1, &uvLvlBuffer);
    glDeleteBuffers(1, &normalBlocBuffer);
    glDeleteBuffers(1, &normalRobotBuffer);
    glDeleteBuffers(1, &normalLvlBuffer);
    glDeleteVertexArrays(1, &vaoRobot);
    glDeleteVertexArrays(1, &vaoBloc);
    glDeleteVertexArrays(1, &vaoLvl);
    glDeleteProgram(programIDBloc);
    glDeleteProgram(programIDRobot);
    glDeleteProgram(programIDLvl);

    glfwTerminate();

    engine->drop();
  }
  return 0; //shutDown(0);

}

