#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D u_Texture;
uniform sampler2D u_PlayerTexture;
uniform sampler2D u_BackgroundTexture;
uniform sampler2D u_GrassTexture;
uniform sampler2D u_PigTexture;
uniform sampler2D u_AppleTexture;

uniform float currentTex = 0.0f;

void main()
{

    switch(int(currentTex))
    {
    case 0:
        color = texture(u_Texture, TexCoord);
        break;
    case 1:
        color = texture(u_PlayerTexture, TexCoord);
        break;
    case 2:
        color = texture(u_PigTexture, TexCoord);
        break;
    case 3:
        color = texture(u_AppleTexture, TexCoord);
        break;
    }
    
}