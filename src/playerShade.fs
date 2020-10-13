#version 330
out vec4 gl_FragColor;
in vec2 TexCoords;
uniform sampler2D Texture;
uniform int scale;
uniform float plus;
uniform float del;
void main()
{
   float rx=((float(TexCoords.x)-del)*(scale)+del);
   vec2 tex=vec2(rx + plus,TexCoords.y);
   gl_FragColor=texture(Texture,tex);
}