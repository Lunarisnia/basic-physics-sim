#ifndef OBJECT_H
#define OBJECT_H
#include "glm/ext/vector_float3.hpp"
#include "shader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
class Object {
public:
  glm::mat4 Position = glm::mat4(1.0f);
  Object(std::vector<float> vertices, std::string fragmentShader,
         std::string vertexShader);
  void Render();
  ~Object();
  void Translate(glm::vec3 position);
  void SetPosition(glm::vec3 position);

private:
  unsigned int VAO, VBO;
  int verticeCount;
  Shader shaderProgram;
};

#endif
