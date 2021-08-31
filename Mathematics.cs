using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mathematics
{
    public static float Dot(Vector3 a, Vector3 b)
    {
        // a = (ax, ay, az)
        // b = (bx, by, bz)
        // dot = ax*bx+ay*by+az*bz
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    public static Vector3 Cross(Vector3 a, Vector3 b)
    {
        // a =      (ax, ay, az)
        // b =      (bx, by, bz)
        // cross =  (ay*bz-az*by,  az*bx-ax*bz, ax*by-ay*bx)
        return new Vector3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
    }

    public static Vector3 Add(Vector3 a, Vector3 b)
    {
        return new Vector3(a.x+b.x, a.y+b.y, a.z+b.z);
    }

    public static Vector3 Subtract(Vector3 a, Vector3 b)
    {
        return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    public static Vector3 Scalar(Vector3 a, float s)
    {
        return new Vector3(a.x*s, a.y*s, a.z*s);
    }
}
