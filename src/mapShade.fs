#version 330
out vec4 gl_FragColor;
uniform sampler2D Texture;
in vec2 TexCoords;
void main()
{
   gl_FragColor=texture(Texture,TexCoords);
}