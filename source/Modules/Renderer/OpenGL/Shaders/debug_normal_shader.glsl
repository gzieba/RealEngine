R""(
#version 410 core

#define MAX_NUMBER_OF_POINT_LIGHTS 5

out vec4 color;

in vec2 outTexCoords;
in vec3 outNormal;
in vec3 outFragPos;

void main(void)
{
    color = vec4(outNormal, 1.0);
}

)""
