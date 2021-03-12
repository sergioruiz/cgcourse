using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Transformations
{
    public enum AXIS    // An enumeration is useful to remember names instead of numbers
    {
        AX_X,           // Value will be set to 0 automatically
        AX_Y,           // Value will be set to 1 automatically
        AX_Z            // Value will be set to 2 automatically
    }

    public static Matrix4x4 TranslateM(float tx, float ty, float tz)
    {
        Matrix4x4 tm = Matrix4x4.identity;
        tm[0, 3] = tx;
        tm[1, 3] = ty;
        tm[2, 3] = tz;
        return tm;
    }

    public static Matrix4x4 ScaleM(float sx, float sy, float sz)
    {
        Matrix4x4 sm = Matrix4x4.identity;
        sm[0, 0] = sx;
        sm[1, 1] = sy;
        sm[2, 2] = sz;
        return sm;
    }

    public static Matrix4x4 RotateM(float angle, AXIS axis)
    {
        Matrix4x4 rm = Matrix4x4.identity;
        float rad = angle * Mathf.Deg2Rad;
        if (axis == AXIS.AX_X)
        {
            rm[1, 1] = Mathf.Cos(rad);
            rm[1, 2] = -Mathf.Sin(rad);
            rm[2, 1] = Mathf.Sin(rad);
            rm[2, 2] = Mathf.Cos(rad);
        }
        else if (axis == AXIS.AX_Y)
        {
            rm[0, 0] = Mathf.Cos(rad);
            rm[0, 2] = Mathf.Sin(rad);
            rm[2, 0] = -Mathf.Sin(rad);
            rm[2, 2] = Mathf.Cos(rad);
        }
        else if (axis == AXIS.AX_Z)
        {
            rm[0, 0] = Mathf.Cos(rad);
            rm[0, 1] = -Mathf.Sin(rad);
            rm[1, 0] = Mathf.Sin(rad);
            rm[1, 1] = Mathf.Cos(rad);
        }
        return rm;
    }

    public static Vector4 Translate(Vector4 original, float x, float y, float z)
    {
        Matrix4x4 t = Matrix4x4.identity;
        t[0, 3] = x;
        t[1, 3] = y;
        t[2, 3] = z;

        return t * original;
    }

    public static Vector4 Translate(Vector4 original, Vector4 translation)
    {
        Matrix4x4 t = Matrix4x4.identity;
        
        t[0, 3] = translation.x;
        t[1, 3] = translation.y;
        t[2, 3] = translation.z;
        t[3, 3] = 1;

        return t * original;
    }

    public static Vector4 Scale(Vector4 original, float x, float y, float z)
    {
        Matrix4x4 s = Matrix4x4.identity;
        s[0, 0] = x;
        s[1, 1] = y;
        s[2, 2] = z;

        return s * original;
    }

    public static Vector4 RotateX(Vector4 original, float degrees)
    {
        float radians = Mathf.Deg2Rad * degrees;
        Matrix4x4 rx = Matrix4x4.identity;
        float cos = Mathf.Cos(radians);
        float sin = Mathf.Sin(radians);

        rx[1, 1] = cos;
        rx[1, 2] = -sin;
        rx[2, 1] = sin;
        rx[2, 2] = cos;

        return rx * original;
    }


    public static Vector4 RotateY(Vector4 original, float degrees)
    {
        float radians = Mathf.Deg2Rad * degrees;
        Matrix4x4 ry = Matrix4x4.identity;
        float cos = Mathf.Cos(radians);
        float sin = Mathf.Sin(radians);

        ry[0, 0] = cos;
        ry[0, 2] = sin;
        ry[2, 0] = -sin;
        ry[2, 2] = cos;

        return ry * original;
    }


    public static Vector4 RotateZ(Vector4 original, float degrees)
    {
        float radians = Mathf.Deg2Rad * degrees;
        Matrix4x4 rz = Matrix4x4.identity;
        float cos = Mathf.Cos(radians);
        float sin = Mathf.Sin(radians);

        rz[0, 0] = cos;
        rz[0, 1] = sin;
        rz[1, 0] = -sin;
        rz[1, 1] = cos;

        return rz * original;

        
    }

}
