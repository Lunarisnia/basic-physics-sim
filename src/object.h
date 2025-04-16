#ifndef OBJECT_H
#define OBJECT_H
#include "glm/ext/vector_float3.hpp"
#include "shader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
const float TIMESTEP = 1.0f / 60.0f;
const glm::vec2 GRAVITY = glm::vec2(0.0f, -10.0f);
class Object {
public:
  glm::mat4 Position = glm::mat4(1.0f);
  glm::vec2 Velocity = glm::vec2(0.0f);
  Shader ShaderProgram;
  glm::vec3 Scale;

  Object(std::vector<float> vertices, std::string fragmentShader,
         std::string vertexShader);
  void Render();
  void SimulatePhysics();
  ~Object();
  void Translate(glm::vec3 position);
  void SetPosition(glm::vec3 position);
  void Resize(glm::vec3 scale);

private:
  unsigned int VAO, VBO;
  int verticeCount;
};

#endif
