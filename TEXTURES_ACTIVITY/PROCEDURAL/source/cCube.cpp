//NPOT = Nearest Power Of Two

#include "cCube.h"

Cube::Cube(float side, bool use_mipmaps)
{
	this->side = side;
	hside = side / 2.0f;

	texture_id = 0;
	// Generate my texture ID (just 1):

}

Cube::~Cube(void)
{
	glDeleteTextures(1, &texture_id);
}

void Cube::draw(void)
{

}
