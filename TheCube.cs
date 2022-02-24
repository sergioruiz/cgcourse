using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TheCube : MonoBehaviour
{
    // 1. Find the new coordinates for each vertex in the cube, after it's translated 3.5 units to the left, 2.2 units down, and 1.7 units forward.
    Vector3[] ApplyTransformations(Vector3[] vertices)
    {
        int number = vertices.Length;
        Vector3[] result = new Vector3[number];
        // 1. Prepare the translation matrix:
        Matrix4x4 t = Transformations.TranslateM(-3.5f, -2.2f, 1.7f);
        for(int i = 0; i < number; i++) // For each vertex...
        {
            Vector3 v = vertices[i];
            Vector4 temp = new Vector4(v.x, v.y, v.z, 1); // Make homogeneous.
            result[i] = t * temp; // Actually apply the transformation!
        }
        return result;
    }

    Vector3[] ApplyTransformations2(Vector3[] vertices)
    {
        int number = vertices.Length;
        Vector3[] result = new Vector3[number];
        // 1. Prepare the translation matrix:
        Matrix4x4 t = Transformations.RotateM(25.0f, Transformations.AXIS.AX_X);
        for (int i = 0; i < number; i++) // For each vertex...
        {
            Vector3 v = vertices[i];
            Vector4 temp = new Vector4(v.x, v.y, v.z, 1); // Make homogeneous.
            result[i] = t * temp; // Actually apply the transformation!
        }
        return result;
    }

    Vector3[] ApplyTransformations3(Vector3[] vertices)
    {
        //3. Find the new coordinates for each vertex of the translated cube, when it rotates -20° around the pivot P=(1, 2, 3) around axis Z.
        int number = vertices.Length;
        Vector3[] result = new Vector3[number];
        // 1. Prepare the translation matrix:
        Matrix4x4 m1 = Transformations.TranslateM(-1, -2, -3);
        Matrix4x4 m2 = Transformations.RotateM(-20.0f, Transformations.AXIS.AX_Z);
        Matrix4x4 m3 = Transformations.TranslateM(1, 2, 3);
        for (int i = 0; i < number; i++) // For each vertex...
        {
            Vector3 v = vertices[i];
            Vector4 temp = new Vector4(v.x, v.y, v.z, 1); // Make homogeneous.
            result[i] = m3 * m2 * m1 * temp; // Actually apply the transformation!
        }
        return result;
    }

    // Start is called before the first frame update
    void Start()
    {
        gameObject.AddComponent<MeshRenderer>();
        MeshFilter mf = gameObject.AddComponent<MeshFilter>();
        Mesh mesh = mf.mesh;
        Vector3[] vertices = new Vector3[]
        {
            new Vector3(-1, -1, 1),   // A
            new Vector3(1, -1, 1),    // B
            new Vector3(1, 1, 1),     // C
            new Vector3(-1, 1, 1)     // D
        }; // Geometry
        int[] triangles = new int[] {   0, 1, 2,
                                        0, 2, 3}; // Topology, front face
        //mesh.vertices = vertices;
        mesh.vertices = ApplyTransformations3(vertices);
        mesh.triangles = triangles;
        mesh.RecalculateNormals();  // Optional, but makes it look better!

        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        MeshFilter smf = sphere.GetComponent<MeshFilter>();
        Mesh sphMesh = smf.mesh;
        smf.mesh.vertices = ApplyTransformations(sphMesh.vertices);
        sphMesh.RecalculateNormals();

    }

    // Update is called once per frame
    void Update()
    {


    }
}

