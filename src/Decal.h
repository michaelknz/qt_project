#ifndef DECAL_H
#define DECAL_H
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Matrix.h"

class Decal {
public:
	Decal(mat4 view, mat4 projection);
	~Decal();
	void DrawDecal(vector3f position);
	void SetAlpha();
	void Update(vector3f position);
	void UpdateCamera(mat4 view);
private:
	Texture* texture;
	Mesh* mesh;
	Shader* shader;
	float alpha;
	float del;
	mat4 view;
	mat4 projection;
	float* vert;
};

#endif