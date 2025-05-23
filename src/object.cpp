#include "object.h"
#include "glm/ext/matrix_transform.hpp"
Object::Object(std::vector<float> vertices, std::string fragmentShader,
               std::string vertexShader)
    : ShaderProgram(Shader(vertexShader.c_str(), fragmentShader.c_str())),
      Scale(1.0f) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // for 2nd argument It seems that what we want is the size total in bytes not
  // the element count
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float),
               &vertices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  verticeCount = vertices.size();
  w = vertices[0];
  h = vertices[1];
}

void Object::Render() {
  ShaderProgram.use();
  ShaderProgram.setMat4("model", Position);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, verticeCount / 3);
}

void Object::Translate(glm::vec3 position) {
  Position = glm::translate(Position, position);
}

void Object::SetPosition(glm::vec3 position) {
  glm::mat4 newPosition = glm::mat4(1.0f);
  newPosition = glm::translate(newPosition, position);
  Position = newPosition;
}

void Object::SimulatePhysics() {
  Velocity.x += GRAVITY.x * TIMESTEP;
  Velocity.y += GRAVITY.y * TIMESTEP;
  Position[3][0] += Velocity.x * TIMESTEP;
  Position[3][1] += Velocity.y * TIMESTEP;

  if (Position[3][0] > 1.0f - w) {
    Position[3][0] = 1.0f - w;
    Velocity.x = -Velocity.x * 0.9f;
    /*Velocity.x = 0.0f;*/
  }
  if (Position[3][0] < -1.0f + w) {
    Position[3][0] = -1.0f + w;
    Velocity.x = -Velocity.x * 0.9f;
    /*Velocity.x = 0.0f;*/
  }
  if (Position[3][1] < -1.0f + h) {
    Position[3][1] = -1.0f + h;
    Velocity.y = -Velocity.y * 0.9f;
  }
  if (Position[3][1] > 1.0f - h) {
    Position[3][1] = 1.0f - h;
    Velocity.y = -Velocity.y * 0.9f;
  }
}

void Object::Resize(glm::vec3 scale) {
  Scale = scale;
  Position = glm::scale(Position, Scale);
}

Object::~Object() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
