#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
//uniform float ambStr = float(1.0);
//uniform vec3 ambColor = vec3(1.0,1.0,1.0);

void main()
{   //vec3 amb = (ambStr*(ambColor))*ourColor;
    //FragColor = texture(ourTexture, TexCoord)*vec4(amb,1.0);
    FragColor = texture(ourTexture,TexCoord)*vec4(ourColor,1.0);
}
