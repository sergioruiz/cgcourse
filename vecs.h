#ifndef __vecs_h
#define __vecs_h

#include <memory>
#include <cmath>
#include <iostream>
using namespace std;

#define DEGTORAD(degree) ((degree) * (3.141592654f / 180.0f))
#define RADTODEG(radian) ((radian) * (180.0f / 3.141592654f))

#ifndef PI
#define PI 3.141593
#endif

#define dotProduct(vec1, vec2)	vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]
#define vecMagnitude(vector) sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2])

void crossProduct(float *, float *, float *);

#define crossProduct(vec1, vec2, res) { res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1]; res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2]; res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0]; }

void unitVector(float *);
float cosAngTwoVecs(float *vec1, float *vec2);
float angTwoVecs(float *vec1, float *vec2);

// Quaternions
#define quatMagnitude(quat) sqrt(quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] + quat[3] * quat[3])
void axisToQuat(float *axis, float ane, float *quat);
void quatToAxis(float *quat, float *axis, float *angle);
void axisToEuler(float *axis, float angle, float *euler);
void quatMult(float *q1, float *q2, float *res);
void unitQuat(float *quat);
void quatInverse(float *quat, float *inv);
void rotatePointAroundAxis(float *point, float *axis, float angle, float *rotPoint);
void rotatePointByQuat(float *point, float *quat, float *rotPoint);

/******************************************************************************/

class vector3f
{
public:

    float x;
    float y;
    float z;

    vector3f(void)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    vector3f(float x_, float y_, float z_);
    void set(float x_, float y_, float z_);
    float length(void);
    void normalize(void);

    // Static utility methods
    static float distance(const vector3f &v1, const vector3f &v2);
    static float dotProd(const vector3f &v1,  const vector3f &v2 );
    static vector3f crossProd(const vector3f &v1, const vector3f &v2);

    // Operators...
    vector3f operator + (const vector3f &other);
    vector3f operator - (const vector3f &other);
    vector3f operator * (const vector3f &other);
    vector3f operator / (const vector3f &other);

    vector3f operator * (const float scalar);
    friend vector3f operator * (const float scalar, const vector3f &other);
    
    vector3f& operator = (const vector3f &other);
    vector3f& operator += (const vector3f &other);
    vector3f& operator -= (const vector3f &other);

    vector3f operator + (void) const;
    vector3f operator - (void) const;
};

/******************************************************************************/

class matrix4x4f
{
public:

    float m[16];

    matrix4x4f()  { identity(); }

    matrix4x4f( float m0, float m4, float  m8, float m12,
                float m1, float m5, float  m9, float m13,
                float m2, float m6, float m10, float m14,
                float m3, float m7, float m11, float m15 );

    matrix4x4f( float *vals);

    void setValues( float *vals);
    void getValues( float *vals);
    void identity(void);
    void translate(const vector3f &trans);
    void translate_x(const float &dist);
    void translate_y(const float &dist);
    void translate_z(const float &dist);
    void rotate(const float &angle, vector3f &axis);
    void rotate_x(const float &angle);
    void rotate_y(const float &angle);
    void rotate_z(const float &angle);
    void scale(const vector3f &scale);
    void transformPoint( vector3f *vec );
    void transformVector( vector3f *vec );

    // Static utility methods
    matrix4x4f invertMatrix( const matrix4x4f *matIn );
    matrix4x4f transpose( const matrix4x4f *matIn );
    
    // Operators...
    matrix4x4f operator + (const matrix4x4f &other);
    matrix4x4f operator - (const matrix4x4f &other);
    matrix4x4f operator * (const matrix4x4f &other);

    matrix4x4f operator * (const float scalar);
};


#endif