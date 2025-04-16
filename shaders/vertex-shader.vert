#version 330
layout(location = 0) in vec3 vertexPosition;

uniform mat4 model;

void main() {
    vec4 position = vec4(vertexPosition, 1.0);
    gl_Position = model * position;
}
