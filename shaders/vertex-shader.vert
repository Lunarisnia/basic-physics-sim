#version 330
layout(location = 0) in vec3 vertexPosition;

uniform mat4 model;
uniform mat4 projection;

void main() {
    vec4 position = vec4(vertexPosition, 1.0f);
    gl_Position = model * position;
}
