using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyCube : MonoBehaviour
{
    public GameObject theOtherGO;

    float dir = 1.0f;    // dir can only be 1 or -1
    float delta = 0.1f;  // how much to change rotation on each frame
    float minAngle = -20.0f;  // minimum rotation angle in X
    float maxAngle = 0.0f;   // maximum rotation angle in X
    float rotationX = 0.0f;  // initial value
    Vector3[] vertices;
    Mesh myMesh1;
    Mesh myMesh2;

    Vector3[] DoTransforms2(Vector3[] input, float rotX)
    {
        Vector3[] output = new Vector3[input.Length];
        Vector4 A = new Vector4(4.772086606f, 3.953410299f, -0.2952625478f, 1);
        Vector4 B = new Vector4(-4.305198646f, -6.389357987f, 3.017512378f, 1);

        for (int i = 0; i < input.Length; i++)
        {
            Vector4 temp1 = input[i];
            temp1.w = 1;
            Vector4 temp2 = Transformations.Translate(temp1, A);    // The center is A
            Vector4 temp3 = Transformations.Translate(temp2, -B);   // Cancel pivot
            Vector4 temp4 = Transformations.RotateX(temp3, rotX);   // Rotate around X
            output[i] = Transformations.Translate(temp4, B);        // Recover pivot
            //Debug.Log(output[i].ToString("F5"));
        }

        return output;
    }

    Vector3[] DoTransforms1(Vector3[] input)
    {
        Vector3[] output = new Vector3[input.Length];

        for (int i = 0; i < input.Length; i++)
        {
            Vector4 temp = input[i];
            temp.w = 1;
            output[i] = Transformations.RotateY(temp, 20.0f);
            Debug.Log(output[i].ToString("F5"));
        }
        return output;
    }


    // Start is called before the first frame update
    void Start()
    {
        /*
        Vector4 v = new Vector4(-0.2279133936f, -0.9198691927f, 4.232664113f, 1);
        Vector4 vt = Transformations.Translate(v, 1.0f, 0.0f, 0.0f);
        Debug.Log(v);
        Debug.Log(vt);


        Vector4 v2 = new Vector4(-0.2279133936f, -0.9198691927f, 4.232664113f, 1);
        Vector4 move = new Vector4(1, 0, 0, 1);
        Vector4 vt2 = Transformations.Translate(v2, move);
        Debug.Log(v2);
        Debug.Log(vt2);
        */


        myMesh1 = new Mesh();
        myMesh2 = new Mesh();
        float side = 10.0f;
        float hSide = side / 2.0f;

        vertices = new Vector3[8]
        {
            new Vector3(-hSide, -hSide, hSide),
            new Vector3(hSide, -hSide, hSide),
            new Vector3(hSide, hSide, hSide),
            new Vector3(-hSide, hSide, hSide),

            new Vector3(hSide, -hSide, -hSide),
            new Vector3(hSide, hSide, -hSide),
            new Vector3(-hSide, -hSide, -hSide),
            new Vector3(-hSide, hSide, -hSide)
        };
        //myMesh.vertices = vertices;
        //myMesh.vertices = DoTransforms1(vertices);
        myMesh1.vertices = DoTransforms2(vertices, rotationX);
        myMesh2.vertices = DoTransforms1(vertices);

        // Topology:
        int[] tris = new int[]
        {
            0, 1, 2,
            0, 2, 3,
            1, 4, 5,
            1, 5, 2,
            4, 6, 7,
            4, 7, 5,
            6, 0, 3,
            6, 3, 7,
            3, 2, 5,
            3, 5, 7,
            1, 0, 6,
            1, 6, 4
        };
        myMesh1.triangles = tris;
        myMesh2.triangles = tris;

        // Normals:
        Vector3[] normals = new Vector3[]
        {
            new Vector3(0,0,-1),
            new Vector3(0,0,-1),
            new Vector3(0,0,-1),
            new Vector3(0,0,-1),
            new Vector3(0,0,-1),
            new Vector3(0,0,-1),
            new Vector3(0,0,-1),
            new Vector3(0,0,-1)
        };
        myMesh1.normals = normals;
        myMesh1.RecalculateNormals();
        myMesh2.normals = normals;
        myMesh2.RecalculateNormals();

        // Mesh:
        MeshRenderer meshRenderer1 = gameObject.AddComponent<MeshRenderer>();
        meshRenderer1.sharedMaterial = new Material(Shader.Find("Standard"));
        MeshFilter meshFilter1 = gameObject.AddComponent<MeshFilter>();
        meshFilter1.mesh = myMesh1;

        MeshRenderer meshRenderer2 = theOtherGO.AddComponent<MeshRenderer>();
        meshRenderer2.sharedMaterial = new Material(Shader.Find("Standard"));
        MeshFilter meshFilter2 = theOtherGO.AddComponent<MeshFilter>();
        meshFilter2.mesh = myMesh2;

    }

    // Update is called once per frame
    void Update()
    {      
        rotationX += dir * delta;
        if (rotationX > maxAngle || rotationX < minAngle) dir = -dir;

        myMesh1.vertices = DoTransforms2(vertices, rotationX);
    }
}
