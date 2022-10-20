#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoord;
uniform mat4 u_MVP;
uniform float facing_right;
uniform float player_being_rendered;
void main()
{
    if (player_being_rendered < 0.5)
           gl_Position = u_MVP * vec4(aPos, 1.0f);
    else if (player_being_rendered > 0.5)
            gl_Position = u_MVP * vec4(aPos, 1.0f);

    if (facing_right > 0.5)
        TexCoord = aTexCoords;
    else{
        TexCoord = -aTexCoords;
    }
    
}