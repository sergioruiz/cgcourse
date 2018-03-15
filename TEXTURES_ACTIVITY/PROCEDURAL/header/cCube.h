#pragma once
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include "freeglut.h"
#endif

#define TEX_SIDE 256

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
	GLuint  texture_id;
};

#endif __CUBE
