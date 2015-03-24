#ifndef GLFWMINIMAL
#define GLFWMINIMAL

void initGLEW();
void initGLFW();
void renderFrame();
void CreateVBO();
void DestroyVBO();
void shutDown(int);
void make_ressources();
void cleanup();
void CreateShaders();
void DestroyShaders();
std::string file_contents(char * fileName);

#endif
