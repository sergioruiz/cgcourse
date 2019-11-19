#include <math.h>
#include "vecs.h"

void unitVector(float *vector){
	float absVal = vecMagnitude(vector);
	if(absVal > 0){
		vector[0] /= absVal;
		vector[1] /= absVal;
		vector[2] /= absVal;
	}
}

float cosAngTwoVecs(float *vec1, float *vec2){
	float dp, sqs1, sqs2;
	dp = dotProduct(vec1, vec2);
	sqs1 = vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2];
	sqs2 = vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2];
	return sqrt(dp * dp / (sqs1 * sqs2));
}

float angTwoVecs(float *vec1, float *vec2){
	return acos(cosAngTwoVecs(vec1, vec2));
}

void axisToQuat(float *axis, float angle, float *quat){
	float cosAng, sinAng;
	cosAng = cos(angle);
	sinAng = sin(angle);
	quat[0] = cosAng;
	quat[1] = axis[0] * sinAng;
	quat[2] = axis[1] * sinAng;
	quat[3] = axis[2] * sinAng;
}

void quatToAxis(float *quat, float *axis, float *angle){
	float sinAng;
	sinAng = sqrt(1 - quat[0] * quat[0]);
	*angle = acos(quat[0]) * 360 / PI;
	if(sinAng != 0){
		axis[0] = quat[1] / sinAng;
		axis[1] = quat[2] / sinAng;
		axis[2] = quat[3] / sinAng;
	} else {
		axis[0] = 1;
		axis[0] = 0;
		axis[0] = 0;
	}
}

void axisToEuler(float *axis, float angle, float *euler){
	float q[4];
	axisToQuat(axis, angle, q);
	euler[0] = atan2(2*q[2]*q[3], q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3]);
	euler[1] = asin(-2*(q[1]*q[3] - q[0]*q[2]));
	euler[2] = atan2(2*(q[1]*q[2]+q[0]*q[3]), q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3]);
}

void rotatePointAroundAxis(float *point, float *axis, float angle, float *rotPoint){
	float quat[4];
	axisToQuat(axis, angle, quat);
	rotatePointByQuat(point, quat, rotPoint);
}

void rotatePointByQuat(float *point, float *quat, float *rotPoint){
	float quatInv[4], quatPoint[4], quatAux1[4], quatAux2[4];
	unitQuat(quat);
	quatPoint[0] = 0;
	quatPoint[1] = point[0];
	quatPoint[2] = point[1];
	quatPoint[3] = point[2];
	unitQuat(quatPoint);
	quatInverse(quat, quatInv);
	quatMult(quat, quatPoint, quatAux1);
	quatMult(quatAux1, quatInv, quatAux2);
	rotPoint[0] = quatAux1[1];
	rotPoint[1] = quatAux1[2];
	rotPoint[2] = quatAux1[3];

}

void quatMult(float *q1, float *q2, float *res){

	float A, B, C, D, E, F, G, H;

	A = (q1[0] + q1[1])*(q2[0] + q2[1]);
	B = (q1[3] - q1[2])*(q2[2] - q2[3]);
	C = (q1[0] - q1[1])*(q2[2] + q2[3]); 
	D = (q1[2] + q1[3])*(q2[0] - q2[1]);
	E = (q1[1] + q1[3])*(q2[1] + q2[2]);
	F = (q1[1] - q1[3])*(q2[1] - q2[2]);
	G = (q1[0] + q1[2])*(q2[0] - q2[3]);
	H = (q1[0] - q1[2])*(q2[0] + q2[3]);


	res[0] = B + (-E - F + G + H) /2;
	res[1] = A - (E + F + G + H)/2; 
	res[2] = C + (E - F + G - H)/2; 
	res[3] = D + (E - F - G + H)/2;
}

void quatInverse(float *quat, float *inv){
	inv[0] =  quat[0];
	inv[1] = -quat[1];
	inv[2] = -quat[2];
	inv[3] = -quat[3];
}

void unitQuat(float *quat){
	float absVal = quatMagnitude(quat);
	if(absVal > 0){
		quat[0] /= absVal;
		quat[1] /= absVal;
		quat[2] /= absVal;
		quat[3] /= absVal;
	}
}

/******************************************************************************/

vector3f::vector3f( float x_, float y_, float z_ )
{
    x = x_;
    y = y_;
    z = z_;
}

void vector3f::set( float x_, float y_, float z_ )
{
    x = x_;
    y = y_;
    z = z_;
}

float vector3f::length( void )
{
    return( (float)sqrt( x * x + y * y + z * z ) );
}

void vector3f::normalize( void )
{
    float fLength = length();

    x = x / fLength;
    y = y / fLength;
    z = z / fLength;
}

// Static utility methods...

static float distance( const vector3f &v1,  const vector3f &v2  )
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;

    return (float)sqrt( dx * dx + dy * dy + dz * dz );
}

static float dotProd( const vector3f &v1,  const vector3f &v2 )
{
    return( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z  );
}

static vector3f crossProd( const vector3f &v1,  const vector3f &v2 )
{
    vector3f vCrossProduct;

    vCrossProduct.x = v1.y * v2.z - v1.z * v2.y;
    vCrossProduct.y = v1.z * v2.x - v1.x * v2.z;
    vCrossProduct.z = v1.x * v2.y - v1.y * v2.x;

    return vCrossProduct;
}

// Operators...

vector3f vector3f::operator + ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x + other.x;
    vResult.y = y + other.y;
    vResult.z = z + other.z;

    return vResult;
}

vector3f vector3f::operator + ( void ) const
{
    return *this;
}

vector3f vector3f::operator - ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x - other.x;
    vResult.y = y - other.y;
    vResult.z = z - other.z;

    return vResult;
}

vector3f vector3f::operator - ( void ) const
{
    vector3f vResult(-x, -y, -z);

    return vResult;
}

vector3f vector3f::operator * ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * other.x;
    vResult.y = y * other.y;
    vResult.z = z * other.z;

    return vResult;
}

vector3f vector3f::operator * ( const float scalar )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * scalar;
    vResult.y = y * scalar;
    vResult.z = z * scalar;

    return vResult;
}

vector3f operator * ( const float scalar, const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = other.x * scalar;
    vResult.y = other.y * scalar;
    vResult.z = other.z * scalar;

    return vResult;
}

vector3f vector3f::operator / ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x / other.x;
    vResult.y = y / other.y;
    vResult.z = z / other.z;

    return vResult;
}

vector3f& vector3f::operator = ( const vector3f &other )
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

vector3f& vector3f::operator += ( const vector3f &other )
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

vector3f& vector3f::operator -= ( const vector3f &other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

/******************************************************************************/

matrix4x4f::matrix4x4f( float m0, float m4, float  m8, float m12,
                        float m1, float m5, float  m9, float m13,
                        float m2, float m6, float m10, float m14,
                        float m3, float m7, float m11, float m15 )
{
    m[0]=m0; m[4]=m4; m[8] =m8;  m[12]=m12;
    m[1]=m1; m[5]=m5; m[9] =m9;  m[13]=m13;
    m[2]=m2; m[6]=m6; m[10]=m10; m[14]=m14;
    m[3]=m3; m[7]=m7; m[11]=m11; m[15]=m15;
}

void matrix4x4f::identity( void )
{
    m[0]=1.0f; m[4]=0.0f; m[8] =0.0f; m[12]=0.0f;
    m[1]=0.0f; m[5]=1.0f; m[9] =0.0f; m[13]=0.0f;
    m[2]=0.0f; m[6]=0.0f; m[10]=1.0f; m[14]=0.0f;
    m[3]=0.0f; m[7]=0.0f; m[11]=0.0f; m[15]=1.0f;
}

void matrix4x4f::setValues(float * vals)
{
	memcpy(m, vals, 16*sizeof(float));
}

void matrix4x4f::getValues(float * vals)
{
	memcpy(vals, m, 16*sizeof(float));
}

void matrix4x4f::translate( const vector3f &trans )
{
    identity();

    m[12] = trans.x;
    m[13] = trans.y;
    m[14] = trans.z;
}

void matrix4x4f::translate_x( const float &dist )
{
    identity();

    m[12] = dist;
}

void matrix4x4f::translate_y( const float &dist )
{
    identity();

    m[13] = dist;
}

void matrix4x4f::translate_z( const float &dist )
{
    identity();

    m[14] = dist;
}

void matrix4x4f::rotate( const float &angle, vector3f &axis )
{
    float s = sin(DEGTORAD(angle));
    float c = cos(DEGTORAD(angle));

    axis.normalize();

    float ux = axis.x;
    float uy = axis.y;
    float uz = axis.z;
    
    m[0]  = c + (1-c) * ux;
    m[1]  = (1-c) * ux*uy + s*uz;
    m[2]  = (1-c) * ux*uz - s*uy;
    m[3]  = 0;
    
    m[4]  = (1-c) * uy*ux - s*uz;
    m[5]  = c + (1-c) * pow(uy,2);
    m[6]  = (1-c) * uy*uz + s*ux;
    m[7]  = 0;
    
    m[8]  = (1-c) * uz*ux + s*uy;
    m[9]  = (1-c) * uz*uz - s*ux;
    m[10] = c + (1-c) * pow(uz,2);
    m[11] = 0;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void matrix4x4f::rotate_x( const float &angle )
{
    float s = sin(DEGTORAD(angle));
    float c = cos(DEGTORAD(angle));

    identity();

    m[5]  =  c;
    m[6]  =  s;
    m[9]  = -s;
    m[10] =  c;
}

void matrix4x4f::rotate_y( const float &angle )
{
    float s = sin(DEGTORAD(angle));
    float c = cos(DEGTORAD(angle));

    identity();

    m[0]  =  c;
    m[2]  = -s;
    m[8]  =  s;
    m[10] =  c;
}

void matrix4x4f::rotate_z( const float &angle )
{
    float s = sin(DEGTORAD(angle));
    float c = cos(DEGTORAD(angle));

    identity();

    m[0] =  c;
    m[1] =  s;
    m[4] = -s;
    m[5] =  c;
}

void matrix4x4f::scale( const vector3f &scale )
{
    identity();

    m[0]  = scale.x;
    m[5]  = scale.y;
    m[10] = scale.z;
}

void matrix4x4f::transformPoint( vector3f *vec )
{
    vector3f &v = *vec;

    float x = v.x;
    float y = v.y;
    float z = v.z;

    v.x = x * m[0] +
          y * m[4] +
          z * m[8] + m[12];

    v.y = x * m[1] +
          y * m[5] +
          z * m[9] + m[13];

    v.z = x * m[2] +
          y * m[6] +
          z * m[10]+ m[14];
}

void matrix4x4f::transformVector( vector3f *vec )
{
    vector3f &v = *vec;

    float x = v.x;
    float y = v.y;
    float z = v.z;

    v.x = x * m[0] +
          y * m[4] +
          z * m[8];

    v.y = x * m[1] +
          y * m[5] +
          z * m[9];

    v.z = x * m[2] +
          y * m[6] +
          z * m[10];
}

matrix4x4f matrix4x4f::operator + ( const matrix4x4f &other )
{
    matrix4x4f result;

    result.m[0]  = m[0]  + other.m[0];
    result.m[1]  = m[1]  + other.m[1];
    result.m[2]  = m[2]  + other.m[2];
    result.m[3]  = m[3]  + other.m[3];

    result.m[4]  = m[4]  + other.m[4];
    result.m[5]  = m[5]  + other.m[5];
    result.m[6]  = m[6]  + other.m[6];
    result.m[7]  = m[7]  + other.m[7];

    result.m[8]  = m[8]  + other.m[8];
    result.m[9]  = m[9]  + other.m[9];
    result.m[10] = m[10] + other.m[10];
    result.m[11] = m[11] + other.m[11];

    result.m[12] = m[12] + other.m[12];
    result.m[13] = m[13] + other.m[13];
    result.m[14] = m[14] + other.m[14];
    result.m[15] = m[15] + other.m[15];

    return result;
}

matrix4x4f matrix4x4f::operator - ( const matrix4x4f &other )
{
    matrix4x4f result;

    result.m[0]  = m[0]  - other.m[0];
    result.m[1]  = m[1]  - other.m[1];
    result.m[2]  = m[2]  - other.m[2];
    result.m[3]  = m[3]  - other.m[3];

    result.m[4]  = m[4]  - other.m[4];
    result.m[5]  = m[5]  - other.m[5];
    result.m[6]  = m[6]  - other.m[6];
    result.m[7]  = m[7]  - other.m[7];

    result.m[8]  = m[8]  - other.m[8];
    result.m[9]  = m[9]  - other.m[9];
    result.m[10] = m[10] - other.m[10];
    result.m[11] = m[11] - other.m[11];

    result.m[12] = m[12] - other.m[12];
    result.m[13] = m[13] - other.m[13];
    result.m[14] = m[14] - other.m[14];
    result.m[15] = m[15] - other.m[15];

    return result;
}

matrix4x4f matrix4x4f::operator * ( const matrix4x4f &other )
{
    matrix4x4f result;

    result.m[0]  = (m[0]*other.m[0])+(m[4]*other.m[1])+(m[8]*other.m[2])+(m[12]*other.m[3]);
    result.m[1]  = (m[1]*other.m[0])+(m[5]*other.m[1])+(m[9]*other.m[2])+(m[13]*other.m[3]);
    result.m[2]  = (m[2]*other.m[0])+(m[6]*other.m[1])+(m[10]*other.m[2])+(m[14]*other.m[3]);
    result.m[3]  = (m[3]*other.m[0])+(m[7]*other.m[1])+(m[11]*other.m[2])+(m[15]*other.m[3]);

    result.m[4]  = (m[0]*other.m[4])+(m[4]*other.m[5])+(m[8]*other.m[6])+(m[12]*other.m[7]);
    result.m[5]  = (m[1]*other.m[4])+(m[5]*other.m[5])+(m[9]*other.m[6])+(m[13]*other.m[7]);
    result.m[6]  = (m[2]*other.m[4])+(m[6]*other.m[5])+(m[10]*other.m[6])+(m[14]*other.m[7]);
    result.m[7]  = (m[3]*other.m[4])+(m[7]*other.m[5])+(m[11]*other.m[6])+(m[15]*other.m[7]);

    result.m[8]  = (m[0]*other.m[8])+(m[4]*other.m[9])+(m[8]*other.m[10])+(m[12]*other.m[11]);
    result.m[9]  = (m[1]*other.m[8])+(m[5]*other.m[9])+(m[9]*other.m[10])+(m[13]*other.m[11]);
    result.m[10] = (m[2]*other.m[8])+(m[6]*other.m[9])+(m[10]*other.m[10])+(m[14]*other.m[11]);
    result.m[11] = (m[3]*other.m[8])+(m[7]*other.m[9])+(m[11]*other.m[10])+(m[15]*other.m[11]);

    result.m[12] = (m[0]*other.m[12])+(m[4]*other.m[13])+(m[8]*other.m[14])+(m[12]*other.m[15]);
    result.m[13] = (m[1]*other.m[12])+(m[5]*other.m[13])+(m[9]*other.m[14])+(m[13]*other.m[15]);
    result.m[14] = (m[2]*other.m[12])+(m[6]*other.m[13])+(m[10]*other.m[14])+(m[14]*other.m[15]);
    result.m[15] = (m[3]*other.m[12])+(m[7]*other.m[13])+(m[11]*other.m[14])+(m[15]*other.m[15]);

    return result;
}

matrix4x4f matrix4x4f::operator * ( const float scalar )
{
    matrix4x4f result;

    result.m[0]  = m[0]  * scalar;
    result.m[1]  = m[1]  * scalar;
    result.m[2]  = m[2]  * scalar;
    result.m[3]  = m[3]  * scalar;

    result.m[4]  = m[4]  * scalar;
    result.m[5]  = m[5]  * scalar;
    result.m[6]  = m[6]  * scalar;
    result.m[7]  = m[7]  * scalar;

    result.m[8]  = m[8]  * scalar;
    result.m[9]  = m[9]  * scalar;
    result.m[10] = m[10] * scalar;
    result.m[11] = m[11] * scalar;

    result.m[12] = m[12] * scalar;
    result.m[13] = m[13] * scalar;
    result.m[14] = m[14] * scalar;
    result.m[15] = m[15] * scalar;

    return result;
}

//-----------------------------------------------------------------------------
// Name: invertMatrix()
// Desc: Performs a highly general un-optimized inversion of a 4x4 matrix.
//-----------------------------------------------------------------------------
matrix4x4f matrix4x4f::invertMatrix( const matrix4x4f *matIn )
{
    matrix4x4f result;

    // OpenGL matrices are column major and can be quite confusing to access 
    // when stored in the typical, one-dimensional array often used by the API.
    // Here are some shorthand conversion macros, which convert a row/column 
    // combination into an array index.
    
    #define MAT(matIn,r,c) matIn->m[c*4+r]

    #define m11 MAT(matIn,0,0)
    #define m12 MAT(matIn,0,1)
    #define m13 MAT(matIn,0,2)
    #define m14 MAT(matIn,0,3)
    #define m21 MAT(matIn,1,0)
    #define m22 MAT(matIn,1,1)
    #define m23 MAT(matIn,1,2)
    #define m24 MAT(matIn,1,3)
    #define m31 MAT(matIn,2,0)
    #define m32 MAT(matIn,2,1)
    #define m33 MAT(matIn,2,2)
    #define m34 MAT(matIn,2,3)
    #define m41 MAT(matIn,3,0)
    #define m42 MAT(matIn,3,1)
    #define m43 MAT(matIn,3,2)
    #define m44 MAT(matIn,3,3)

    // Inverse = adjoint / det. (See linear algebra texts.)

    // pre-compute 2x2 dets for last two rows when computing
    // cofactors of first two rows.
    float d12 = (m31 * m42 - m41 * m32);
    float d13 = (m31 * m43 - m41 * m33);
    float d23 = (m32 * m43 - m42 * m33);
    float d24 = (m32 * m44 - m42 * m34);
    float d34 = (m33 * m44 - m43 * m34);
    float d41 = (m34 * m41 - m44 * m31);

    float tmp[16];
    
    tmp[0] =  (m22 * d34 - m23 * d24 + m24 * d23);
    tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
    tmp[2] =  (m21 * d24 + m22 * d41 + m24 * d12);
    tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

    // Compute determinant as early as possible using these cofactors.
    float det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

    // Run singularity test.
    if( det == 0.0 )
    {
        cout << "Warning: Call to invertMatrix produced a Singular matrix." << endl;

        float identity[16] = 
        {
           1.0, 0.0, 0.0, 0.0,
           0.0, 1.0, 0.0, 0.0,
           0.0, 0.0, 1.0, 0.0,
           0.0, 0.0, 0.0, 1.0
        };

       memcpy( result.m, identity, 16*sizeof(float) );
    }
    else
    {
       float invDet = 1.0f / det;
       
       // Compute rest of inverse.
       tmp[0] *= invDet;
       tmp[1] *= invDet;
       tmp[2] *= invDet;
       tmp[3] *= invDet;

       tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
       tmp[5] =  (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
       tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
       tmp[7] =  (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

       // Pre-compute 2x2 dets for first two rows when computing cofactors 
       // of last two rows.
       d12 = m11 * m22 - m21 * m12;
       d13 = m11 * m23 - m21 * m13;
       d23 = m12 * m23 - m22 * m13;
       d24 = m12 * m24 - m22 * m14;
       d34 = m13 * m24 - m23 * m14;
       d41 = m14 * m21 - m24 * m11;

       tmp[8]  =  (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
       tmp[9]  = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
       tmp[10] =  (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
       tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
       tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
       tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
       tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
       tmp[15] =  (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

       memcpy( result.m, tmp, 16*sizeof(float) );
    }

    #undef m11
    #undef m12
    #undef m13
    #undef m14
    #undef m21
    #undef m22
    #undef m23
    #undef m24
    #undef m31
    #undef m32
    #undef m33
    #undef m34
    #undef m41
    #undef m42
    #undef m43
    #undef m44
    #undef MAT
    
    return result;
}

//-----------------------------------------------------------------------------
// Name: transpose()
// Desc: 
//-----------------------------------------------------------------------------
matrix4x4f matrix4x4f::transpose( const matrix4x4f *matIn )
{
    matrix4x4f result;

    result.m[0]  = matIn->m[0];
    result.m[1]  = matIn->m[4];
    result.m[2]  = matIn->m[8];
    result.m[3]  = matIn->m[12];

    result.m[4]  = matIn->m[1];
    result.m[5]  = matIn->m[5];
    result.m[6]  = matIn->m[9];
    result.m[7]  = matIn->m[13];

    result.m[8]  = matIn->m[2];
    result.m[9]  = matIn->m[6];
    result.m[10] = matIn->m[10];
    result.m[11] = matIn->m[14];

    result.m[12] = matIn->m[3];
    result.m[13] = matIn->m[7];
    result.m[14] = matIn->m[11];
    result.m[15] = matIn->m[15];

    return result;
}
