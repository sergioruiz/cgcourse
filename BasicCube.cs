using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyMesh : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Vector3[] points = new Vector3[8]
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

        int[] indices = new int[36]
        {
            0, 1, 2, 0, 2, 3,   // FRONT
            1, 4, 5, 1, 5, 2,   // RIGHT
            4, 6, 7, 4, 7, 5,   // BACK
            6, 0, 3, 6, 3, 7,   // LEFT
            3, 2, 5, 3, 5, 7,   // TOP
            1, 0, 6, 1, 6, 4   // BOTTOM
        };

        Mesh triangleMesh = new Mesh();
        triangleMesh.vertices = points;
        triangleMesh.triangles = indices;

        MeshRenderer mr = gameObject.AddComponent<MeshRenderer>();
        mr.sharedMaterial = new Material(Shader.Find("Standard"));
        MeshFilter mf = gameObject.AddComponent<MeshFilter>();
        mf.mesh = triangleMesh;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
