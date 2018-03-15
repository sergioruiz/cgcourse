#include "cCube.h"

Cube::Cube( float side, bool use_mipmaps )
{
	this->side = side;
	hside = side / 2.0f;


}

Cube::~Cube( void )
{
	glDeleteTextures( 1, &targas[0].texID );
	glDeleteTextures( 1, &targas[1].texID );
	glDeleteTextures( 1, &targas[2].texID );
	glDeleteTextures( 1, &targas[3].texID );
	glDeleteTextures( 1, &targas[4].texID );
	glDeleteTextures( 1, &targas[5].texID );
}

void Cube::draw( void )
{

}
