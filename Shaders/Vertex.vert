#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoord;

uniform mat4 u_MVP;
uniform float facing_right;
uniform float u_xTextureOffset;
uniform float u_yTextureOffset;
uniform float u_xInverseOffset;

void main()
{
      gl_Position = u_MVP * vec4(aPos, 1.0f);  

      if (facing_right > 0.5)
           TexCoord = aTexCoords + vec2(u_xTextureOffset, -u_yTextureOffset);
      else{
           TexCoord = -aTexCoords - vec2(u_xInverseOffset, 0.0f) - vec2(u_xTextureOffset, -u_yTextureOffset);
       }


}