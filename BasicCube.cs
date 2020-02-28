/*
 * TC3022. Computer Graphics 
 * Sergio Ruiz-Loza, Ph.D.
 * 
 * Basic script for a cube.
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicCube : MonoBehaviour
{
    private Mesh cubeMesh;      // Unity's mesh: vertices and triangles.
    private Vector3[] points;   // Our own vertices.
    private int[] indices;      // Our own triangles.
    private MeshFilter mf;

    // Start is called before the first frame update
    void Start()
    {
        points = new Vector3[8]         // Points for a cube.
        {
            new Vector3(-1, -1,  1),    // A
            new Vector3(1,  -1,  1),    // B
            new Vector3(1,   1,  1),    // C
            new Vector3(-1,  1,  1),    // D
            new Vector3(1,  -1, -1),    // E
            new Vector3(1,   1, -1),    // F
            new Vector3(-1, -1, -1),    // G
            new Vector3(-1,  1, -1)     // H
        };

        indices = new int[36]           // Faces for a cube.
        {
            0, 1, 2, 0, 2, 3,           // FRONT
            1, 4, 5, 1, 5, 2,           // RIGHT
            4, 6, 7, 4, 7, 5,           // BACK
            6, 0, 3, 6, 3, 7,           // LEFT
            3, 2, 5, 3, 5, 7,           // TOP
            1, 0, 6, 1, 6, 4            // BOTTOM
        };

        cubeMesh = new Mesh();          // Instance of a Unity Mesh.
        cubeMesh.vertices = points;     // Assign our vertices to the Mesh.
        cubeMesh.triangles = indices;   // Assign our faces to the Mesh.

        MeshRenderer mr = gameObject.AddComponent<MeshRenderer>();
        mr.sharedMaterial = new Material(Shader.Find("Standard"));
        mf = gameObject.AddComponent<MeshFilter>();
        mf.mesh = cubeMesh;             // Make the Mesh visible.
        mf.mesh.RecalculateNormals();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public Mesh getMesh()
    {
        return mf.mesh;
    }

    public Vector3[] getPoints()
    {
        return points;
    }

    public int[] getIndices()
    {
        return indices;
    }

    public void setPoints(Vector3[] ps)
    {
        if (ps.Length == points.Length)
        {
            mf.mesh.vertices = ps; // Change the points to 'ps'.
            mf.mesh.RecalculateNormals();
        }
    }

    public void resetPoints()
    {
        mf.mesh.vertices = points; // Back to the original points.
        mf.mesh.RecalculateNormals();
    }
}
