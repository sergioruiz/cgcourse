#pragma once
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include "freeglut.h"
#endif
#include "cTexture.h"

#ifndef __CUBE
#define __CUBE

class Cube
{
public:
			Cube	(	float	side,
						bool	use_mipmaps	);
			~Cube	(	void				);

	void	draw	(	void				);

private:
	float	side;
	float	hside;
	Texture targas[6];
};

#endif __CUBE
