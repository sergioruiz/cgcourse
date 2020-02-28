/*
 * TC3022. Computer Graphics 
 * Sergio Ruiz-Loza, Ph.D.
 * 
 * Basic script for an animated arm.
 * Uses BasicCube.cs
 */


using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicArm : MonoBehaviour
{
    public GameObject bcPrefab;
    BasicCube bc1;          // This will be a script type. An instance of BasicCube.cs
    BasicCube bc2;          // This will be a script type. An instance of BasicCube.cs
    float zRot = 0.0f;      // Starting rotation angle.
    float zDir = 1.0f;      // Starting direction for rotation.

    // Start is called before the first frame update
    void Start()
    {
        // Instantiate a BasicCubePrefab, then get its BasicCube.cs script.
        bc1 = Instantiate(bcPrefab).GetComponent<BasicCube>();
        bc2 = Instantiate(bcPrefab).GetComponent<BasicCube>();
    }

    void Update()
    {
        // Always add DIRECTION * DELTA to the rotation
        zRot += zDir * 0.4f;
        // Change direction with the threshold (0, 60):
        if (zRot > 60.0f || zRot < 0.0f) zDir = -zDir;

        // Change the angle to radians for the first arm link:
        float rad = zRot * Mathf.Deg2Rad;
        // Change the angle to radians for the second arm link:
        float rad2 = zRot * 0.75f * Mathf.Deg2Rad;

        // Prepare a matrix to transform the first link:
        Matrix4x4 transform = Matrix4x4.identity;
        // Rotation matrix around Z:
        Matrix4x4 rotZ = Matrix4x4.identity;
        rotZ[0, 0] = Mathf.Cos(rad);
        rotZ[0, 1] = -Mathf.Sin(rad);
        rotZ[1, 0] = Mathf.Sin(rad);
        rotZ[1, 1] = Mathf.Cos(rad);
        // Translation matrix to the right:
        Matrix4x4 right = Matrix4x4.identity;
        right[0, 3] = 1.0f;
        // Scale matrix for 1/2 in Y and 1/2 in Z:
        Matrix4x4 scale = Matrix4x4.identity;
        scale[1, 1] = 0.5f;
        scale[2, 2] = 0.5f;

        // Keep the transformation without scale for the 2nd link:
        Matrix4x4 transformNoScale = rotZ * right;
        // Make the transform matrix for the first link:
        transform = rotZ * right * scale;
        //Debug.Log(transform);

        // Process the second link:
        Matrix4x4 transform2 = transformNoScale;
        Matrix4x4 rotZ2 = Matrix4x4.identity;
        rotZ2[0, 0] = Mathf.Cos(rad2);
        rotZ2[0, 1] = -Mathf.Sin(rad2);
        rotZ2[1, 0] = Mathf.Sin(rad2);
        rotZ2[1, 1] = Mathf.Cos(rad2);

        transform2 = transform2 * right * rotZ2 * right * scale;

        // Reset both links before transforming them:
        bc1.resetPoints();
        bc2.resetPoints();

        // Finally, transform both links from their original points:
        TransformMesh(bc1.getMesh(), transform);
        TransformMesh(bc2.getMesh(), transform2);
    }

    void TransformMesh(Mesh m, Matrix4x4 t)
    {
        Vector3[] points = m.vertices;
        int total = points.Length;
        for (int i = 0; i < total; i++)
        {
            Vector4 v = new Vector4(points[i].x,
                                    points[i].y,
                                    points[i].z, 1);
            v = t * v;
            points[i] = new Vector3(v.x, v.y, v.z);
        }
        m.vertices = points;
        m.RecalculateNormals();
    }

}
