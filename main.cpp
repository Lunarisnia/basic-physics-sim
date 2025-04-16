#include "src/object.h"
#include "src/stb_image.h"
#include <glad/glad.h>
// FORCE
#include "src/shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // ============= GLFW Window Creation
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // ============= GLAD Loading
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  std::vector<float> vertices = {
      0.5f, 0.5f, 0.0f,   //
      -0.5f, 0.5f, 0.0f,  //
      0.5f, -0.5f, 0.0f,  //
                          //
      -0.5f, -0.5f, 0.0f, //
      -0.5f, 0.5f, 0.0f,  //
      0.5f, -0.5f, 0.0f   //
  };
  Object plane(vertices, "./shaders/diffuse.frag",
               "./shaders/vertex-shader.vert");

  while (!glfwWindowShouldClose(window)) {
    currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glm::vec3 planePos = glm::vec3(glm::sin((float)glfwGetTime()), 0.0f, 0.0f);
    plane.SetPosition(planePos);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    plane.Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}
