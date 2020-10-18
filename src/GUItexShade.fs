# version 330

out vec4 gl_FragColor;
uniform sampler2D Texture;
uniform vec3 color_mul;
in vec2 TexCoord;
void main()
{
   gl_FragColor=texture(Texture,TexCoord)*vec4(color_mul,1.0f);
}  