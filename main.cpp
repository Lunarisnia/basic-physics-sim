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

  float w1 = 0.25f;
  float h1 = 0.25f;
  std::vector<float> vertices = {
      w1, h1, 0.0f,   //
      -w1, h1, 0.0f,  //
      w1, -h1, 0.0f,  //
                      //
      -w1, -h1, 0.0f, //
      -w1, h1, 0.0f,  //
      w1, -h1, 0.0f   //
  };
  glm::vec3 planePos = glm::vec3(1.0f, 0.0f, 0.0f);
  Object plane(vertices, "./shaders/diffuse.frag",
               "./shaders/vertex-shader.vert");
  plane.SetPosition(planePos);
  /*plane.Resize(glm::vec3(0.6f, 0.25f, 1.0f));*/
  plane.Velocity.x = -0.4f;
  plane.Velocity.y = 0.6f;

  float w2 = 0.25f;
  float h2 = 0.25f;
  std::vector<float> vertices2 = {
      w2, h2, 0.0f,   //
      -w2, h2, 0.0f,  //
      w2, -h2, 0.0f,  //
                      //
      -w2, -h2, 0.0f, //
      -w2, h2, 0.0f,  //
      w2, -h2, 0.0f   //
  };
  glm::vec3 planePos2 = glm::vec3(-1.0f, 0.0f, 0.0f);
  Object plane2(vertices2, "./shaders/diffuse.frag",
                "./shaders/vertex-shader.vert");
  plane2.SetPosition(planePos2);
  /*plane.Resize(glm::vec3(0.6f, 0.25f, 1.0f));*/
  plane2.Velocity.x = 0.4f;
  plane2.Velocity.y = 0.6f;

  // TODO: Collision detection / trigger

  while (!glfwWindowShouldClose(window)) {
    currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::vec3 p1 = glm::vec3(plane.Position[3][0], plane.Position[3][1],
                             plane.Position[3][2]);
    glm::vec3 p2 = glm::vec3(plane2.Position[3][0], plane2.Position[3][1],
                             plane2.Position[3][2]);

    if (p1.x < p2.x + w2 && p1.x + w1 > p2.x && p1.y < p2.y + h2 &&
        p1.y + h1 > p2.y) {
      /*std::cout << "Collided!" << std::endl;*/
      plane.Velocity.x = -plane.Velocity.x * 0.5f;
      plane2.Velocity.x = -plane2.Velocity.x * 0.5f;
    }

    plane.SimulatePhysics();
    plane2.SimulatePhysics();

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
    plane2.Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}
