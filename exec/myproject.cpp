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

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "utils/textures.h"
#include "utils/controls.h"

#define WIDTH 1024
#define HEIGHT 768

GLFWwindow* window;

char keyOnce[GLFW_KEY_LAST + 1];
#define glfwGetKeyOnce(WINDOW, KEY)             \
    (glfwGetKey(WINDOW, KEY) ?              \
     (keyOnce[KEY] ? false : (keyOnce[KEY] = true)) :   \
     (keyOnce[KEY] = false))

inline glm::vec3 torusPoint(double theta, double phi, double R, double r)/*{{{*/
{
  //!todo You may implement the correct formula for the torus point here
  double x = (R+r*cos(phi))*cos(theta);
  double y = (R+r*cos(phi))*sin(theta);
  double z = r*sin(phi);
  return glm::vec3(x+1,y,z);
}/*}}}*/

inline glm::vec3 torusNormal(double theta, double phi)/*{{{*/
{
    //!todo You may implement the correct formula for the torus normal here
  double x = cos(theta);
  double y = sin(theta);
  double z = sin(phi);
  return glm::vec3(x,y,z);
}/*}}}*/

void makeAColoredTorus(std::vector<glm::vec3>& verticesTorus, std::vector<glm::vec3>& colorsTorus, std::vector<unsigned int>& indicesTorus, double R, double r, int nbBins)
{
    for(int i=0;i<nbBins;i++){
      for(int j=0;j<nbBins;j++){
	double theta = i*2*M_PI/nbBins;
	double phi = j*2*M_PI/nbBins;
	double zColor = r*sin(phi);
	verticesTorus.push_back(torusPoint(theta,phi,R,r));
	colorsTorus.push_back(glm::vec3((zColor+r)/(2*r),0,(r-zColor)/(2*r)));
      }
    }
    int n = verticesTorus.size();
    for(unsigned int k=0;k<n;k++){
      indicesTorus.push_back(k);
      indicesTorus.push_back((k+nbBins)%n);
      indicesTorus.push_back((k+1)%n);
      indicesTorus.push_back((k+1)%n);
      indicesTorus.push_back((k+nbBins)%n);
      indicesTorus.push_back((k+nbBins+1)%n);
    }
}

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


  /*********************** Cube **************************/
  GLuint programid = shader_loader("myproject.v.glsl","myproject.f.glsl");
  
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  //---------CPU side version
  float positions[]={0,0,0, 0,1,0, 1,0,0,   1,0,0, 0,1,0, 1,1,0, 
		     0,0,0, 1,0,0, 0,0,1,   0,0,1, 1,0,0, 1,0,1, 
		     0,0,0, 0,0,1, 0,1,0,   0,1,0, 0,0,1, 0,1,1, 
		     0,0,1, 1,0,1, 0,1,1,   0,1,1, 1,0,1, 1,1,1,
		     1,0,0, 1,1,0, 1,0,1,   1,0,1, 1,1,0, 1,1,1,
		     0,1,0, 0,1,1, 1,1,0,   1,1,0, 0,1,1, 1,1,1};
  GLuint vertexCount = 36;

  unsigned int indices[vertexCount];
  for(unsigned int i=0;i<vertexCount;i++){
    indices[i] = i;
  }
  GLuint indexCount = 36;
  
  glm::vec3 colors[vertexCount];
  for(unsigned int i=0;i<vertexCount;i++){
    if(i<6) colors[i]=glm::vec3(1,0,0);
    if(i>=6 && i<12) colors[i]=glm::vec3(1,1,0);
    if(i>=12 && i<18) colors[i]=glm::vec3(0,1,0);
    if(i>=18 && i<24) colors[i]=glm::vec3(0,1,1);
    if(i>=24 && i<30) colors[i]=glm::vec3(0,0,1);
    if(i>=30) colors[i]=glm::vec3(1,0,1);
    }

  //---------GPU side version
  GLuint positionBuffer;
  glGenBuffers(1, &positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertexCount* 3 * sizeof(float), positions, GL_STATIC_DRAW);
  GLint positionIndex = glGetAttribLocation(programid, "position");
  glEnableVertexAttribArray(positionIndex);
  glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint indexBuffer;
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount* sizeof(unsigned int), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

  GLuint colorBuffer;
  glGenBuffers(1, &colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  GLint colorIndex = glGetAttribLocation(programid, "vColor");
  glEnableVertexAttribArray(colorIndex);
  glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(colorIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);


  /*********************** Tore **************************/
  
  GLuint vaoTore;
  glGenVertexArrays(1, &vaoTore);
  glBindVertexArray(vaoTore);
  //---------CPU side version
  std::vector<glm::vec3> verticesTorus;
  std::vector<glm::vec3> colorsTorus;
  std::vector<unsigned int> indicesTorus;
  
  makeAColoredTorus(verticesTorus, colorsTorus, indicesTorus, 2, 0.5, 100);

  //---------GPU side version
  GLuint positionTorusBuffer;
  glGenBuffers(1, &positionTorusBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionTorusBuffer);
  glBufferData(GL_ARRAY_BUFFER, verticesTorus.size()*sizeof(glm::vec3), &verticesTorus[0], GL_STATIC_DRAW);
  GLint positionTorusIndex = glGetAttribLocation(programid, "position");
  glEnableVertexAttribArray(positionTorusIndex);
  glVertexAttribPointer(positionTorusIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionTorusIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint indexTorusBuffer;
  glGenBuffers(1, &indexTorusBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexTorusBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesTorus.size()*sizeof(unsigned int), &indicesTorus[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

  GLuint colorTorusBuffer;
  glGenBuffers(1, &colorTorusBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorTorusBuffer);
  glBufferData(GL_ARRAY_BUFFER, colorsTorus.size()*sizeof(glm::vec3), &colorsTorus[0], GL_STATIC_DRAW);
  GLint colorTorusIndex = glGetAttribLocation(programid, "vColor");
  glEnableVertexAttribArray(colorTorusIndex);
  glVertexAttribPointer(colorTorusIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(colorTorusIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  /**************** Plan ********************/
  GLuint programidPlan = shader_loader("mytexture.v.glsl","mytexture.f.glsl");
  
  GLuint vaoPlan;
  glGenVertexArrays(1, &vaoPlan);
  glBindVertexArray(vaoPlan);
  //---------CPU side version
  float positionsPlan[]={0,0,0, 0,0,1, 0,1,0,   0,1,0, 0,0,1, 0,1,1};
  GLuint vertexCountPlan = 6;
  
  GLuint texturePlan = loadTGATexture("brick_colormap.tga");
  GLuint texturePlanID = glGetUniformLocation(programidPlan, "colorMap");

  std::vector<glm::vec2> uvs={
        glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,0),
        glm::vec2(1,0),  glm::vec2(0,1), glm::vec2(1,1)
  };

  //---------GPU side version
  GLuint positionPlanBuffer;
  glGenBuffers(1, &positionPlanBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionPlanBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertexCountPlan* 3 * sizeof(float), positionsPlan, GL_STATIC_DRAW);
  GLint positionPlanIndex = glGetAttribLocation(programidPlan, "position");
  glEnableVertexAttribArray(positionPlanIndex);
  glVertexAttribPointer(positionPlanIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(positionPlanIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint uvBuffer;
  glGenBuffers(1, &uvBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
  GLint uvIndex = glGetAttribLocation(programidPlan, "uv");
  glEnableVertexAttribArray(uvIndex);
  glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDisableVertexAttribArray(uvIndex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  
  /***************** Test Matrice *****************/

  int brique[5][5] = {{1,0,0,1,0},
		      {0,1,0,0,0},
		      {0,1,0,1,0},
		      {0,0,0,1,1},
		      {0,0,0,0,1}};
  glm::vec3 translations[25];
  int nbBrique = 0;
  float offset = 0.1f;
  for(int y=0; y<5; y+=1){
    for(int z=0; z<5; z+=1){
      if(brique[y][z]){
	glm::vec3 translation;
	translation.x = 0.0f;
	translation.y = -(float)y + offset;
	translation.z = (float)z + offset;
	translations[nbBrique++] = translation;
      }
    }
  }  
  int indexBrique = 0;
  GLuint indexBriqueID = glGetUniformLocation(programidPlan, "selected");

  /**********************************************************/

  GLuint MatrixID = glGetUniformLocation(programid, "MVP");
  GLuint MatrixIDPlan = glGetUniformLocation(programidPlan, "MVP");
  /* 
  glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 View       = glm::lookAt(
				     glm::vec3(-1,4,4),
				     glm::vec3(0.5,0.5,0.5),
				     glm::vec3(0,1,0) 
				     );
  glm::mat4 Model      = glm::mat4(1.0f);
  glm::mat4 MVP        = Projection * View * Model;*/

  /*********************** Boucle **************************/

  while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programid);

    glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 ViewMatrix = computeMatricesFromInputs(/*WIDTH,HEIGHT,*/window);
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    //Cube
    glBindVertexArray(vao);
    glEnableVertexAttribArray(positionIndex);
    glEnableVertexAttribArray(colorIndex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(positionIndex);
    glDisableVertexAttribArray(colorIndex);
    glBindVertexArray(0);

    //Tore
    glBindVertexArray(vaoTore);
    glEnableVertexAttribArray(positionTorusIndex);
    glEnableVertexAttribArray(colorTorusIndex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexTorusBuffer);
    glDrawElements(GL_TRIANGLES, indicesTorus.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(positionTorusIndex);
    glDisableVertexAttribArray(colorTorusIndex);
    glBindVertexArray(0);

    //Plan
    glUseProgram(0);
    glUseProgram(programidPlan);

    if(glfwGetKeyOnce(window, GLFW_KEY_T) == GLFW_PRESS){
      if(indexBrique<nbBrique-1) indexBrique++;
    }
    if(glfwGetKeyOnce(window, GLFW_KEY_G) == GLFW_PRESS){
      if(indexBrique>0) indexBrique--;
    }
    glUniform1i(indexBriqueID, indexBrique);

    if(glfwGetKeyOnce(window, GLFW_KEY_W) == GLFW_PRESS){
      translations[indexBrique].y += 1.0f;
    }
    if(glfwGetKeyOnce(window, GLFW_KEY_A) == GLFW_PRESS){
      translations[indexBrique].z -= 1.0f;
    }
    if(glfwGetKeyOnce(window, GLFW_KEY_S) == GLFW_PRESS){
      translations[indexBrique].y -= 1.0f;
    }
    if(glfwGetKeyOnce(window, GLFW_KEY_D) == GLFW_PRESS){
      translations[indexBrique].z += 1.0f;
    }
    if(glfwGetKeyOnce(window, GLFW_KEY_F) == GLFW_PRESS){
      translations[indexBrique].x -= 1.0f;
    }
    if(glfwGetKeyOnce(window, GLFW_KEY_R) == GLFW_PRESS){
      translations[indexBrique].x += 1.0f;
    }

    for(int i=0; i<nbBrique; i++){
      std::stringstream ss;
      std::string index;
      ss << i; 
      index = ss.str(); 
      GLuint translID = glGetUniformLocation(programidPlan, ("transl[" + index + "]").c_str());
      glUniform3f(translID, translations[i].x, translations[i].y, translations[i].z);
    }  

    glm::mat4 ModelMatrixPlan = glm::translate(glm::mat4(1.0),glm::vec3(4.0f,0.0f,0.0f));
    glm::mat4 MVPPlan = ProjectionMatrix * ViewMatrix * ModelMatrixPlan;
    glUniformMatrix4fv(MatrixIDPlan, 1, GL_FALSE, &MVPPlan[0][0]);

    glBindVertexArray(vaoPlan);
    glEnableVertexAttribArray(positionPlanIndex);
    glEnableVertexAttribArray(uvIndex);

    glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCountPlan, nbBrique);

    glDisableVertexAttribArray(positionPlanIndex);
    glDisableVertexAttribArray(uvIndex);
    glBindVertexArray(0);

    /*************/
    glfwSwapBuffers(window);
    glfwPollEvents();

    glBindVertexArray(0);
    glUseProgram(0);
  }


  /*********************** Nettoyage **************************/

  glDeleteBuffers(1, &positionBuffer);
  glDeleteBuffers(1, &colorBuffer);
  glDeleteBuffers(1, &indexBuffer);
  glDeleteBuffers(1, &positionTorusBuffer);
  glDeleteBuffers(1, &colorTorusBuffer);
  glDeleteBuffers(1, &indexTorusBuffer);
  glDeleteBuffers(1, &positionPlanBuffer);
  glDeleteBuffers(1, &uvBuffer);
  glDeleteVertexArrays(1, &vao);
  glDeleteVertexArrays(1, &vaoTore);
  glDeleteVertexArrays(1, &vaoPlan);
  glDeleteProgram(programid);
  glDeleteProgram(programidPlan);

  glfwTerminate();

  return 0; //shutDown(0);

}

