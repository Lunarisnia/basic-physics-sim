#ifndef OBJECT_H
#define OBJECT_H
#include "shader.h"
#include <glad/glad.h>
#include <string>
#include <vector>
class Object {
public:
  Object(std::vector<float> vertices, std::string fragmentShader,
         std::string vertexShader);
  void Render();
  ~Object();

private:
  unsigned int VAO, VBO;
  int verticeCount;
  Shader shaderProgram;
};

#endif
