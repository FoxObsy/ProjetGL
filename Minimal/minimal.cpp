/* Include headers*//*{{{*/
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
// matrix and vectors
// to declare before including glm.hpp, to use the swizzle operators
#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
//loading stuffs
#include "utils/utils.h"
#include "utils/shaders.h"
#include "utils/textures.h"
#include "utils/objloader.h"
#include "../include/lightGlAPI.hpp"
#include "minimal.hpp"/*}}}*/


//-------------------- MAIN /*{{{*/
int main(void)/*{{{*/
{
    init();
    mainLoop();
    shutDown(0);
}/*}}}*/

void mainLoop(void)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    // this just loops as long as the program runs
    while(!glfwWindowShouldClose(controls.window))
    {
        /* Calculate time elapsed, and the amount by which stuff rotates*//*{{{*/
        double current_time = glfwGetTime();
        controls.setTime(current_time);
        controls.updateView();
        /*}}}*/

        /* Additional key handling (when repeat key is needed)*//*{{{*/
        // escape to quit, arrow keys to rotate view
        if (glfwGetKey(controls.window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(controls.window, 'Q') == GLFW_PRESS)
            break;
        controls.continuousKeyCallback();
        /*}}}*/

        /* Send all the drawing commands and swap the buffers*//*{{{*/
        draw();
        // swap back and front buffers
        glfwSwapBuffers(controls.window);
        glfwPollEvents();
        controls.resetView();
        /*}}}*/
    }
}/*}}}*/
/*}}}*/


//-------------------- Inits/*{{{*/
void init(void)/*{{{*/
{ 
    //-------------------- Globals/*{{{*/
    unsigned int nbEx=4;
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Renderer* renderer=new ensi::gl::GLRenderer();
    scene.setRenderer(renderer);
    ensi::gl::Controls& controls=scene.controls;
    controls.nbExercises=nbEx;
    /*}}}*/
    /* GLFW initialization *//*{{{*/
    const int window_width = 1024, window_height = 800;
    if (!glfwInit())
        shutDown(1);
    // Create OpenGL 3.x Core Profile Context                                                   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#endif
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 800 x 600, default bit color, 32 bit depth, no alpha or stencil buffers, windowed
    controls.window=glfwCreateWindow(window_width, window_height, "Minimal OpenGL application with GLFW", NULL, NULL);
    if (!controls.window)
    {
        std::cerr<<"Could not open a window"<<std::endl;
        shutDown(1);
    }
    glfwMakeContextCurrent(controls.window);
    /*}}}*/
    
    /* GLEW Initialization *//*{{{*/
    // Do not forget to use glewExperimental so that glewInit works with core
    // profile: http://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    std::cout<<"Here, we should expect to get a GL_INVALID_ENUM (that's a known bug), and indeed:"<<std::endl;
    checkGLerror();
    if (GlewInitResult != GLEW_OK) {
        std::cerr<<"ERROR: "<< glewGetErrorString(GlewInitResult)<<std::endl;
        shutDown(1);
    }/*}}}*/
    
    /* GLFW callbak definitions *//*{{{*/
    glfwSetFramebufferSizeCallback(controls.window, &resize);
    glfwSetKeyCallback(controls.window, keyCallback);
    glfwSetMouseButtonCallback(controls.window, mouseButtonCallback);
    /*}}}*/
    
    /* Creating the controls*//*{{{*/
    int width;
    int height;
    glfwGetFramebufferSize(controls.window, &width, &height);
    resize(controls.window, width, height);
    /*}}}*/

    /* Creating OpenGL resources *//*{{{*/
    make_resources();
    std::cout<<"Seems we made it "<<std::endl;
    std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;/*}}}*/
}/*}}}*/

int make_resources(void)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    //!Important: Set the attribute locations:
    // Now create a program
    ensi::gl::Program prog("simple.v.glsl", "simple.f.glsl");
    // Create a material
    ensi::gl::GLSLMaterial material;
    material.program=prog;
    scene.materials["simple"]=material;
    // Create the scene/*{{{*/
    glm::mat4 mw;
    ensi::gl::Mesh cube;
    makeAPerFaceColoredCube(cube);
    // cube/*{{{*/
    mw=controls.modelWorldMatrix.top();
    mw=glm::scale(mw, glm::vec3(2,2,2));
    scene.addObject("cube", cube, mw);/*}}}*/
    // torus/*{{{*/
    ensi::gl::Mesh torus;
    makeAColoredTorus(torus, 1, 0.25, 50);
    mw=controls.modelWorldMatrix.top();
    mw=glm::scale(mw, glm::vec3(2,2,2));
    mw=glm::rotate(mw, glm::pi<float>()/4, glm::vec3(2,2,2));
    scene.addObject("torus", torus, mw);/*}}}*/
    /*}}}*/
    return 1;
}/*}}}*/
/*}}}*/


void draw()/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT );
    if(controls.exercise>=1)
    {
        /*!todo exercise 1: Enable back face culling *//*{{{*/
        /*}}}*/
    }
    if(controls.exercise>=3)
    {
        /*!todo exercise 3: Enable depth test *//*{{{*/
        /*}}}*/
    }
    scene.drawObject("cube","simple");
    if(controls.exercise>=2)
        scene.drawObject("torus","simple");
    checkGLerror();
    if(controls.exercise>=1)
    {
        /*!todo exercise 1: Disable back face culling *//*{{{*/
        /*}}}*/
    }
    if(controls.exercise>=3)
    {
        /*!todo exercise 3: Disable depth test *//*{{{*/
        /*}}}*/
    }
}
/*}}}*/

/*Geometry construction {{{*/
void makeAPerFaceColoredCube(ensi::gl::Mesh& cube)/*{{{*/
{
    using ensi::gl::Vertex;
    cube.m_verts.clear();
    cube.m_tris.clear();
    std::vector<glm::vec3> ps, ns, ts, bs;
    std::vector<glm::vec2> uvs;
    //make the front face (y=0)/*{{{*/
    glm::vec3 p0(0,0,0);
    glm::vec3 p1(1,0,0);
    glm::vec3 p2(1,0,1);
    glm::vec3 p3(0,0,1);
    glm::vec3 n0(0,-1,0);
    glm::vec3 n1(0,-1,0);
    glm::vec3 n2(0,-1,0);
    glm::vec3 n3(0,-1,0);  
    glm::vec3 pp0(0,1,0);
    glm::vec3 pp1(0,1,1);
    glm::vec3 pp2(1,1,1);
    glm::vec3 pp3(1,1,0);
    glm::vec3 nn0(0,1,0);
    glm::vec3 nn1(0,1,0);
    glm::vec3 nn2(0,1,0);
    glm::vec3 nn3(0,1,0);  /*}}}*/
    // for each axis create two faces
    for (int i = 0; i < 3; ++i)/*{{{*/
    {
        int ix=i, iy=(i+1)%3, iz=(i+2)%3;
        // first face
        ps.push_back(glm::vec3(p0[ix]-0.5,p0[iy]-0.5,p0[iz]-0.5));
        ns.push_back(glm::vec3(n0[ix],n0[iy],n0[iz]));
        uvs.push_back(glm::vec2(p0[0],p0[2]));

        ps.push_back(glm::vec3(p1[ix]-0.5,p1[iy]-0.5,p1[iz]-0.5));
        ns.push_back(glm::vec3(n1[ix],n1[iy],n1[iz]));
        uvs.push_back(glm::vec2(p1[0],p1[2]));

        ps.push_back(glm::vec3(p2[ix]-0.5,p2[iy]-0.5,p2[iz]-0.5));
        ns.push_back(glm::vec3(n2[ix],n2[iy],n2[iz]));
        uvs.push_back(glm::vec2(p2[0],p2[2]));


        ps.push_back(glm::vec3(p0[ix]-0.5,p0[iy]-0.5,p0[iz]-0.5));
        ns.push_back(glm::vec3(n0[ix],n0[iy],n0[iz]));
        uvs.push_back(glm::vec2(p0[0],p0[2]));

        ps.push_back(glm::vec3(p2[ix]-0.5,p2[iy]-0.5,p2[iz]-0.5));
        ns.push_back(glm::vec3(n2[ix],n2[iy],n2[iz]));
        uvs.push_back(glm::vec2(p2[0],p2[2]));

        ps.push_back(glm::vec3(p3[ix]-0.5,p3[iy]-0.5,p3[iz]-0.5));
        ns.push_back(glm::vec3(n3[ix],n3[iy],n3[iz]));
        uvs.push_back(glm::vec2(p3[0],p3[2]));


        // second face
        ps.push_back(glm::vec3(pp0[ix]-0.5,pp0[iy]-0.5,pp0[iz]-0.5));
        ns.push_back(glm::vec3(nn0[ix],nn0[iy],nn0[iz]));
        uvs.push_back(glm::vec2(pp0[0],pp0[2]));

        ps.push_back(glm::vec3(pp1[ix]-0.5,pp1[iy]-0.5,pp1[iz]-0.5));
        ns.push_back(glm::vec3(nn1[ix],nn1[iy],nn1[iz]));
        uvs.push_back(glm::vec2(pp1[0],pp1[2]));

        ps.push_back(glm::vec3(pp2[ix]-0.5,pp2[iy]-0.5,pp2[iz]-0.5));
        ns.push_back(glm::vec3(nn2[ix],nn2[iy],nn2[iz]));
        uvs.push_back(glm::vec2(pp2[0],pp2[2]));


        ps.push_back(glm::vec3(pp0[ix]-0.5,pp0[iy]-0.5,pp0[iz]-0.5));
        ns.push_back(glm::vec3(nn0[ix],nn0[iy],nn0[iz]));
        uvs.push_back(glm::vec2(pp0[0],pp0[2]));

        ps.push_back(glm::vec3(pp2[ix]-0.5,pp2[iy]-0.5,pp2[iz]-0.5));
        ns.push_back(glm::vec3(nn2[ix],nn2[iy],nn2[iz]));
        uvs.push_back(glm::vec2(pp2[0],pp2[2]));

        ps.push_back(glm::vec3(pp3[ix]-0.5,pp3[iy]-0.5,pp3[iz]-0.5));
        ns.push_back(glm::vec3(nn3[ix],nn3[iy],nn3[iz]));
        uvs.push_back(glm::vec2(pp3[0],pp3[2]));

    }/*}}}*/
    computeTangentBasis(ps, uvs, ns, ts, bs);
    std::vector<glm::vec3> ops, ons, ots, obs;
    std::vector<glm::vec2> ouvs;
    indexVBO_TBN(ps, uvs, ns, ts, bs, cube.m_tris, ops, ouvs, ons, ots, obs);
    const glm::vec4 colors[]={glm::vec4(1,0,0,1), glm::vec4(1,1,0,1), glm::vec4(0,1,0,1), glm::vec4(0,1,1,1), glm::vec4(0,0,1,1), glm::vec4(1,0,1,1)};
    for (unsigned int i = 0; i < ops.size(); ++i)
    {
        Vertex v(ops[i], ons[i], ouvs[i], colors[i/4], ots[i]);
        cube.m_verts.push_back(v);
    }
    cube.computeBSphere();
}
/*}}}*/

inline glm::vec3 torusPoint(double theta, double phi, double R, double r)/*{{{*/
{
    //!todo You may implement the correct formula for the torus point here
    return glm::vec3();
}/*}}}*/

inline glm::vec3 torusNormal(double theta, double phi)/*{{{*/
{
    //!todo You may implement the correct formula for the torus normal here
    return glm::vec3 ();
}/*}}}*/

void makeAColoredTorus(ensi::gl::Mesh& torus, double R, double r, int nbBins)/*{{{*/
{
    using ensi::gl::Vertex;
    torus.m_verts.clear();
    torus.m_tris.clear();
     /*!todo exercise 2: build up a torus {{{
      * You may find useful to implement the parametric formula in the torusPoint
      * and torusNormal functions.
      **/
    /*}}}*/
}/*}}}*/
/*}}}*/


//-------------------- GLFW Callbacks/*{{{*/
void shutDown(int return_code)/*{{{*/
{
    glfwTerminate();
    exit(return_code);
}/*}}}*/

void resize(GLFWwindow* window, int width, int height)/*{{{*/
{        
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    controls.resize(width, height);
}/*}}}*/

void keyCallback(GLFWwindow* window, int key, int scancode,  int action, int modifiers)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    controls.keyCallback(key, action, modifiers);
}/*}}}*/

void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    controls.mouseButtonCallback(button, action);
}/*}}}*/
/*}}}*/
// vim: foldmethod=marker autoread:
