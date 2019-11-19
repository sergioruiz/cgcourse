#include "Camera.h"

Camera::Camera(){
	pos[0] = pos[1] = pos[2] = 0;
	dir[0] = 1;
	dir[1] = 0;
	dir[2] = 1;
	up[0] = 0;
	up[1] = 1;
	up[2] = 0;
	pivot[0] = pivot[1] = pivot[2] = 0;
	near_plane = 1.0;
	far_plane = 64;
	fov = 45;
	tang = (float)tan(GRAD2RAD * fov * 0.5) ;
	
}

void Camera::init(){
	pos[0] = pos[1] = pos[2] = 0;
	dir[0] = 1;
	dir[1] = 0;
	dir[2] = 1;
	up[0] = 0;
	up[1] = 1;
	up[2] = 0;
	pivot[0] = pivot[1] = pivot[2] = 0;
	near_plane = 1.0;
	far_plane = 64;
	fov = 45;
}


void Camera::setPos(float x, float y, float z){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Camera::setDirVec(float x, float y, float z){
	float mag = sqrt(x*x+y*y+z*z);
	if(mag > 0){
		dir[0] = x/mag;
		dir[1] = y/mag;
		dir[2] = z/mag;
	}
}

void Camera::setUpVec(float x, float y, float z){
	float mag = sqrt(x*x+y*y+z*z);
	if(mag > 0){
		up[0] = x/mag;
		up[1] = y/mag;
		up[2] = z/mag;
	}
}

void Camera::setPivot(float x, float y, float z){
	pivot[0] = x;
	pivot[1] = y;
	pivot[2] = z;
}

void Camera::moveForward(float dist){
	pos[0] += dist*dir[0];
	pos[1] += dist*dir[1];
	pos[2] += dist*dir[2];
}

void Camera::moveBackward(float dist){
	pos[0] -= dist*dir[0];
	pos[1] -= dist*dir[1];
	pos[2] -= dist*dir[2];
}

void Camera::moveRight(float dist){
	float right[3];
	crossProduct(dir, up, right);
	pos[0] += dist*right[0];
	pos[1] += dist*right[1];
	pos[2] += dist*right[2];
}

void Camera::moveLeft(float dist){
	float right[3];
	crossProduct(dir, up, right);
	pos[0] -= dist*right[0];
	pos[1] -= dist*right[1];
	pos[2] -= dist*right[2];
}

void Camera::moveUp(float dist){
	pos[0] += dist*up[0];
	pos[1] += dist*up[1];
	pos[2] += dist*up[2];
}

void Camera::moveDown(float dist){
	pos[0] -= dist*up[0];
	pos[1] -= dist*up[1];
	pos[2] -= dist*up[2];
}

void Camera::move(float dist, float angle){
	float right[3], moveDir[3];
	float cosAng, sinAng, radAng;

	radAng = angle*M_PI/180.0;
	cosAng = cos(radAng);
	sinAng = sin(radAng);

	crossProduct(dir, up, right);

	moveDir[0] = dir[0]*cosAng - right[0]*sinAng;
	moveDir[1] = dir[1]*cosAng - right[1]*sinAng;
	moveDir[2] = dir[2]*cosAng - right[2]*sinAng;

	pos[0] += dist*moveDir[0];
	pos[1] += dist*moveDir[1];
	pos[2] += dist*moveDir[2];
}

void Camera::setAgentCamera(float *p, float d, float height){
//void Camera::setAgentCamera(Agent *agent){
	this->dir[0] = cos(d * 3.1415927 / 180);
	this->dir[1] = 0;
	this->dir[2] = sin(d * 3.1415927 / 180);

	this->pos[0] = p[0] - (dir[0]*1.0);
	this->pos[2] = p[1] - (dir[2]*1.0);

	this->pos[1] = height;
}

#define CAMERA_ROTATE_AXIS

void Camera::rotate(float angle, float x, float y, float z){
	float newDir[3], newUp[3], axis[3], radAng;
#ifdef CAMERA_ROTATE_AXIS
	float origAxis[3];
	float right[3];

	crossProduct(dir, up, right);
	origAxis[0] = x;
	origAxis[1] = y;
	origAxis[2] = z;
	unitVector(origAxis);
	axis[0] = origAxis[0]*right[0] + origAxis[1]*up[0] + origAxis[2]*dir[0];
	axis[1] = origAxis[0]*right[1] + origAxis[1]*up[1] + origAxis[2]*dir[1];
	axis[2] = origAxis[0]*right[2] + origAxis[1]*up[2] + origAxis[2]*dir[2];
#else
	axis[0] = x;
	axis[1] = y;
	axis[2] = z;
	unitVector(axis);
#endif
	radAng = angle * 3.1415927 / 180.0;
	rotatePointAroundAxis(dir, axis, radAng, newDir);
	rotatePointAroundAxis(up,  axis, radAng, newUp);

	dir[0] = newDir[0];
	dir[1] = newDir[1];
	dir[2] = newDir[2];
	up[0]  = newUp[0];
	up[1]  = newUp[1];
	up[2]  = newUp[2];
}

void Camera::moveAround(float angle, float x, float y, float z){
	float negPos[3];
	float newDir[3], newUp[3], newPos[3], axis[3], radAng;
	float distPivot;
#ifdef CAMERA_ROTATE_AXIS
	float origAxis[3];
	float right[3];

	crossProduct(dir, up, right);
	origAxis[0] = x;
	origAxis[1] = y;
	origAxis[2] = z;
	unitVector(origAxis);
	axis[0] = origAxis[0]*right[0] + origAxis[1]*up[0] + origAxis[2]*dir[0];
	axis[1] = origAxis[0]*right[1] + origAxis[1]*up[1] + origAxis[2]*dir[1];
	axis[2] = origAxis[0]*right[2] + origAxis[1]*up[2] + origAxis[2]*dir[2];
#else
	axis[0] = x;
	axis[1] = y;
	axis[2] = z;
	unitVector(axis);
#endif

	negPos[0] = pos[0] - pivot[0];
	negPos[1] = pos[1] - pivot[1];
	negPos[2] = pos[2] - pivot[2];
	distPivot = vecMagnitude(negPos);
	unitVector(negPos);

	radAng = -angle * 3.1415927 / 180.0;

	rotatePointAroundAxis(negPos, axis, radAng, newPos);
	rotatePointAroundAxis(dir,    axis, radAng, newDir);
	rotatePointAroundAxis(up,     axis, radAng, newUp);

	pos[0] = pivot[0] + newPos[0]*distPivot;
	pos[1] = pivot[1] + newPos[1]*distPivot;
	pos[2] = pivot[2] + newPos[2]*distPivot;
	dir[0] = newDir[0];
	dir[1] = newDir[1];
	dir[2] = newDir[2];
	up[0]  = newUp[0];
	up[1]  = newUp[1];
	up[2]  = newUp[2];

}

void Camera::getWorldFrustumCoords(float *coords){
	float tans[2];
	int viewportDims[4];
	float vecX[3];
	float deltaNear[3][3], deltaFar[3][3];
	float dx, dy;
	float aspect;

	glGetIntegerv(GL_VIEWPORT, viewportDims);
	aspect = (float) viewportDims[2] / (float) viewportDims[3];
	tans[1] = tan(fov/2.0);
	tans[0] = tans[1] * aspect;
//	crossProduct(dir, up, vecX);
	crossProduct(up, dir, vecX);

	dx = near_plane * tans[0]; //nearW
	dy = near_plane * tans[1]; // nearH
	deltaNear[0][0] = vecX[0] * dx; 
	deltaNear[0][1] = vecX[1] * dx;
	deltaNear[0][2] = vecX[2] * dx;
	deltaNear[1][0] = up[0]   * dy;
	deltaNear[1][1] = up[1]   * dy;
	deltaNear[1][2] = up[2]   * dy;
	deltaNear[2][0] = dir[0]  * near_plane;
	deltaNear[2][1] = dir[1]  * near_plane;
	deltaNear[2][2] = dir[2]  * near_plane;

	dx = far_plane * tans[0];
	dy = far_plane * tans[1];
	deltaFar[0][0] = vecX[0] * dx;
	deltaFar[0][1] = vecX[1] * dx;
	deltaFar[0][2] = vecX[2] * dx;
	deltaFar[1][0] = up[0]   * dy;
	deltaFar[1][1] = up[1]   * dy;
	deltaFar[1][2] = up[2]   * dy;
	deltaFar[2][0] = dir[0]  * far_plane;
	deltaFar[2][1] = dir[1]  * far_plane;
	deltaFar[2][2] = dir[2]  * far_plane;

	coords[0]  = pos[0] - deltaNear[0][0] - deltaNear[1][0] + deltaNear[2][0];
	coords[1]  = pos[1] - deltaNear[0][1] - deltaNear[1][1] + deltaNear[2][1];
	coords[2]  = pos[2] - deltaNear[0][2] - deltaNear[1][2] + deltaNear[2][2];
	coords[3]  = pos[0] + deltaNear[0][0] - deltaNear[1][0] + deltaNear[2][0];
	coords[4]  = pos[1] + deltaNear[0][1] - deltaNear[1][1] + deltaNear[2][1];
	coords[5]  = pos[2] + deltaNear[0][2] - deltaNear[1][2] + deltaNear[2][2];
	coords[6]  = pos[0] - deltaNear[0][0] + deltaNear[1][0] + deltaNear[2][0];
	coords[7]  = pos[1] - deltaNear[0][1] + deltaNear[1][1] + deltaNear[2][1];
	coords[8]  = pos[2] - deltaNear[0][2] + deltaNear[1][2] + deltaNear[2][2];
	coords[9]  = pos[0] + deltaNear[0][0] + deltaNear[1][0] + deltaNear[2][0];
	coords[10] = pos[1] + deltaNear[0][1] + deltaNear[1][1] + deltaNear[2][1];
	coords[11] = pos[2] + deltaNear[0][2] + deltaNear[1][2] + deltaNear[2][2];

	coords[12] = pos[0] - deltaFar[0][0] - deltaFar[1][0] + deltaFar[2][0];
	coords[13] = pos[1] - deltaFar[0][1] - deltaFar[1][1] + deltaFar[2][1];
	coords[14] = pos[2] - deltaFar[0][2] - deltaFar[1][2] + deltaFar[2][2];
	coords[15] = pos[0] + deltaFar[0][0] - deltaFar[1][0] + deltaFar[2][0];
	coords[16] = pos[1] + deltaFar[0][1] - deltaFar[1][1] + deltaFar[2][1];
	coords[17] = pos[2] + deltaFar[0][2] - deltaFar[1][2] + deltaFar[2][2];
	coords[18] = pos[0] - deltaFar[0][0] + deltaFar[1][0] + deltaFar[2][0];
	coords[19] = pos[1] - deltaFar[0][1] + deltaFar[1][1] + deltaFar[2][1];
	coords[20] = pos[2] - deltaFar[0][2] + deltaFar[1][2] + deltaFar[2][2];
	coords[21] = pos[0] + deltaFar[0][0] + deltaFar[1][0] + deltaFar[2][0];
	coords[22] = pos[1] + deltaFar[0][1] + deltaFar[1][1] + deltaFar[2][1];
	coords[23] = pos[2] + deltaFar[0][2] + deltaFar[1][2] + deltaFar[2][2];

}

void Camera::draw(){
	float coords[24];
	//float linePoints[24];

	getWorldFrustumCoords(coords);

	GLboolean enabled=false;
	glGetBooleanv(GL_LIGHTING, &enabled);
	if (enabled)
		glDisable(GL_LIGHTING);
	
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);

	glBegin(GL_LINE_STRIP);
		glVertex3f(coords[0],  coords[1],  coords[2]); //nbr
		glVertex3f(coords[3],  coords[4],  coords[5]); //nbl
		glVertex3f(coords[9],  coords[10], coords[11]);//ntl
		glVertex3f(coords[6],  coords[7],  coords[8]); //ntr	
		glVertex3f(coords[0],  coords[1],  coords[2]);
		glVertex3f(coords[12], coords[13], coords[14]);
		glVertex3f(coords[18], coords[19], coords[20]);
		glVertex3f(coords[6],  coords[7],  coords[8]);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
		glVertex3f(coords[15], coords[16], coords[17]); //fbl
		glVertex3f(coords[12], coords[13], coords[14]); //fbr
		glVertex3f(coords[18], coords[19], coords[20]); //ftr
		glVertex3f(coords[21], coords[22], coords[23]); //ftl
		glVertex3f(coords[15], coords[16], coords[17]);
		glVertex3f(coords[3],  coords[4],  coords[5]);
		glVertex3f(coords[9],  coords[10], coords[11]);
		glVertex3f(coords[21], coords[22], coords[23]);
	glEnd();

	if (enabled)
		glEnable(GL_LIGHTING);
}

void Camera::setView(){
	int viewportCoords[4];

	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (GLfloat)viewportCoords[2] / (GLfloat)viewportCoords[3], near_plane, far_plane);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		pos[0], pos[1], pos[2],
		pos[0]+dir[0], pos[1]+dir[1], pos[2]+dir[2], 
		up[0], up[1], up[2]);
}

void Camera::readMatrices(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	setView();
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
//	glMatrixMode(GL_PROJECTION);
//	glMultMatrixf(modelviewMatrix);
//	glGetFloatv(GL_PROJECTION_MATRIX, modelviewProjectionMatrix);
//	glMatrixMode(GL_MODELVIEW);
//	glMultMatrixf(projectionMatrix);
//	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
/*
void Camera::initVisibility(int res){
	if(visMap == NULL){
		visMap = new VisibilityMap();
		visMap->width = visMap->height = res;
		visMap->pos[0] = visMap->pos[1] = 0;
		visMap->pos[2] = -1;
		visMap->size[0] = visMap->size[1] = visMap->size[2] = res;
		visMap->allocData();
	}
}
*/
/*
void Camera::updateVisibility(){
	visMap->updateVisibility2d(this);
}
*/
void Camera::normalize(float *p)
{
	double len;

	len = sqrt (p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
	if (len > 0.0){
		p[0] /= len,
		p[1] /= len,
		p[2] /= len;
	}
	else {
		p[0] = 0,
		p[1] = 0,
		p[2] = 0;
	}
}

