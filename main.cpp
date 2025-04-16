#include "glm/ext/matrix_clip_space.hpp"
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

glm::vec2 gravity(0.0f, -10.0f);

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
  // f = m * a
  glm::vec3 planePos = glm::vec3(0.0f, 0.0f, 0.0f);
  Object plane(vertices, "./shaders/diffuse.frag",
               "./shaders/vertex-shader.vert");
  plane.Resize(glm::vec3(0.6f, 0.25f, 1.0f));
  plane.Velocity.x = 0.6f;
  plane.Velocity.y = 0.6f;

  while (!glfwWindowShouldClose(window)) {
    currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    plane.SimulatePhysics();

    processInput(window);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.5f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 0.0f, 800.0f, 600.0f, 1.0f, -2.0f);
    plane.ShaderProgram.use();
    plane.ShaderProgram.setMat4("projection", projection);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    plane.Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}
