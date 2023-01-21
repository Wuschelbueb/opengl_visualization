// Preprocessor Directives
#ifndef OPENGLVISUALIZATION
#define OPENGLVISUALIZATION

// ImGui Headers
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Object loader Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// Matrix Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
#include <stb_image.h>

// Additional Headers
#include <shader.hpp>
#include <camera.hpp>
#include <model.hpp>

// nfd header
#include <nfd.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>

// Define Some Constants
int mWidth = 1920;
int mHeight = 1080;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 origin;
glm::vec3 cameraStartPosition;
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;
glm::mat4 projection;
// mouse movement
bool leftButtonPressed = false;
bool showObject = false, whiteTexture = false;
int lastMouseX = 0;
int lastMouseY = 0;
float pitch = 0.f;
float yaw = 0.f;

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double mouseX, double mouseY);
void mouse_button(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void initModel(std::string const &path, Shader &ourShader, Model &ourModel);
void loadModel(const string &path, Model &ourModel, int &nbQuads, int &upperThreshold, Camera &camera, bool &showObject);

#endif
