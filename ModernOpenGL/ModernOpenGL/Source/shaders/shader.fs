#version 330 core
out vec4 FragColor;
  
in vec3 FragPos;  
in vec3 Normal; 
in vec2 TexCoord;


uniform vec3 lightPos;
uniform vec3 viewPos;  
uniform sampler2D ourTexture;

void main()
{
     FragColor = texture(ourTexture, TexCoord);
}
