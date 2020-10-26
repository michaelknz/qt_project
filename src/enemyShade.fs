#version 330

in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D Texture;
uniform vec3 color;
uniform int scale;
uniform float plus;
uniform float del;

void main(){
    float rx=((float(TexCoord.x)-del)*(scale)+del);
    vec2 tex=vec2(rx+plus,TexCoord.y);
    FragColor=texture(Texture,tex)*vec4(color,1.0f);
}
