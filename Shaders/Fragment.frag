#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D u_Texture;
uniform sampler2D u_PlayerTexture;
uniform sampler2D u_BackgroundTexture;
uniform sampler2D u_GrassTexture;
uniform sampler2D u_PigTexture;
uniform sampler2D u_AppleTexture;
uniform sampler2D u_OrangeTexture;
uniform sampler2D u_AngryBlockTexture;

uniform sampler2D u_textures[32];

uniform float currentTex = 0.0f;
uniform float u_Color;
uniform float u_Opacity;

void main()
{

    switch(int(currentTex))
    {
    case 0:
        color = texture(u_textures[0], TexCoord);
        break;
    case 1:
        color = texture(u_textures[1], TexCoord) * vec4(u_Color, u_Color, u_Color, u_Opacity);
        break;
    case 2:
        color = texture(u_textures[2], TexCoord);
        break;
    case 3:
        color = texture(u_textures[3], TexCoord);
        break;
    case 4:
        color = texture(u_textures[4], TexCoord);
        break;
    case 5:
        color = texture(u_textures[5], TexCoord);
        break;
    case 6:
        color = texture(u_textures[6], TexCoord);
        break;
    case 7:
        color = texture(u_textures[7], TexCoord);
        break;
    case 8:
        color = texture(u_textures[8], TexCoord);
        break;
    case 9:
        color = texture(u_textures[9], TexCoord);
        break;  
    case 15:
        color = texture(u_textures[15], TexCoord);
        break;
   
    }
    
}