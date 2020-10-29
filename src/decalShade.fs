#version 330

in vec2 TexCoord;
uniform sampler2D Texture;
uniform float alpha;

out vec4 FragCoord;

void main(){
   FragCoord=texture(Texture,TexCoord)*vec4(1.0f,1.0f,1.0f,alpha);
}