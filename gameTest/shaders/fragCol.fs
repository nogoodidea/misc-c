#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 ourColor;
in vec3 normal;

uniform vec3 lCol = vec3(1.0,1.0,1.0);
uniform vec3 lightPos = vec3(0.0,0.0,1.0);
void main()
{
    //ambient
    float ambStr = 0.1;
    vec3 ambient = ambStr*lCol;

    //diff    
    vec3 lightDir = normalize(lightPos - pos);
    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = vec3(diff*lCol);

    //light out
    vec3 light = (ambient + diffuse)*ourColor;
    //FragColor = vec4(light, 1.0);
    FragColor = vec4(normal, 1.0);
}
