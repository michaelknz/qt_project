#include "MapBg.h"

MapBg::MapBg() {
	
}

void MapBg::Init(const std::string& filename, mat4 view, mat4 proj) {
	projection = proj;
	this->view = view;
	tile_height = 0.15f;
	tile_width = 0.15f;
	texture = new Texture(filename.c_str());
	shader = new Shader("mapShade");
	SetRoomMap();
	SetTexMap();
	SetVerts();
	mesh = new Mesh(verts, Map_height * Map_width * 6 * 5);
}

void MapBg::SetRoomMap() {
	Map_width = 32;
	Map_height = 16;
	tile_tex_width = 8;
	tile_tex_height = 8;
	Map = new char[Map_height * Map_width + 1];
	Map = "EUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUC"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFDFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "AUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUB";
}

void MapBg::SetTexMap() {
	SetTexMapUnit('A', 0, 1, 7, 8);
	SetTexMapUnit('D', 9, 10, 6, 7);
	SetTexMapUnit('U', 1, 2, 9, 10);
	SetTexMapUnit('R', 3, 4, 8, 9);
	SetTexMapUnit('L', 0, 1, 8, 9);
	SetTexMapUnit('F', 1, 2, 8, 9);
	SetTexMapUnit('B', 3, 4, 7, 8);
	SetTexMapUnit('C', 3, 4, 9, 10);
	SetTexMapUnit('E', 0, 1, 9, 10);
}

void MapBg::SetTexMapUnit(char a, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy) {
	TexCoordMap[a].min_x = (float)(minx * (tile_tex_width)) / (float)texture->Width();
	TexCoordMap[a].max_x = (float)(maxx * (tile_tex_width)) / (float)texture->Width();
	TexCoordMap[a].min_y = (float)(miny * (tile_tex_height)) / (float)texture->Height();
	TexCoordMap[a].max_y = (float)(maxy * (tile_tex_height)) / (float)texture->Height();
}

void MapBg::SetVerts() {
	verts = new float[Map_height * Map_width * 6 * 5];
	float del_x = tile_width;
	float del_y = tile_height;
	float x = -tile_width * (float)Map_width / 2.0f;
	float y = tile_height * (float)Map_height / 2.0f;
	float tmp_x = x;
	float tmp_y = y;
	int j = 0;
	for (int i = 0; i < Map_height; ++i) {
		for (int j = 0; j < Map_width; ++j) {
			int e = (i * Map_width + j) * 30;
			int u = (i * Map_width + j);
			verts[e] = tmp_x; verts[e + 1] = tmp_y; verts[e + 2] = 0.0f; verts[e + 3] = TexCoordMap[Map[u]].min_x; verts[e + 4] = TexCoordMap[Map[u]].max_y;
			verts[e + 5] = tmp_x + del_x; verts[e + 6] = tmp_y; verts[e + 7] = 0.0f; verts[e + 8] = TexCoordMap[Map[u]].max_x; verts[e + 9] = TexCoordMap[Map[u]].max_y;
			verts[e + 10] = tmp_x; verts[e + 11] = tmp_y - del_y; verts[e + 12] = 0.0f; verts[e + 13] = TexCoordMap[Map[u]].min_x; verts[e + 14] = TexCoordMap[Map[u]].min_y;
			verts[e + 15] = tmp_x + del_x; verts[e + 16] = tmp_y; verts[e + 17] = 0.0f; verts[e + 18] = TexCoordMap[Map[u]].max_x; verts[e + 19] = TexCoordMap[Map[u]].max_y;
			verts[e + 20] = tmp_x + del_x; verts[e + 21] = tmp_y - del_y; verts[e + 22] = 0.0f; verts[e + 23] = TexCoordMap[Map[u]].max_x; verts[e + 24] = TexCoordMap[Map[u]].min_y;
			verts[e + 25] = tmp_x; verts[e + 26] = tmp_y - del_y; verts[e + 27] = 0.0f; verts[e + 28] = TexCoordMap[Map[u]].min_x; verts[e + 29] = TexCoordMap[Map[u]].min_y;
			tmp_x += del_x;
		}
		tmp_y -= del_y;
		tmp_x = x;
	}
}

void MapBg::DrawMapBg() {
	shader->bind();
	texture->bind();
	shader->SetUniformMatrix4fv("projection", Matrix::Transplon(projection));
	shader->SetUniformMatrix4fv("view", Matrix::Transplon(view));
	mesh->Draw_Mesh();
	texture->unbind();
	shader->unbind();
}

void MapBg::ShutUp() {
	delete texture;
	delete mesh;
	delete shader;
	delete[] verts;
	delete[] Map;
}

MapBg::~MapBg() {

}