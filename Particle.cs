using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Particle : MonoBehaviour
{
    public float mass;
    public float g;         // gravedad
    public float r;         // radio
    public float rc;        // Restitution Coefficient (elastic=1, inelastic = 0)
    public Vector3 p;       // position
    public Vector3 forces;
    public Color color;
    public Vector3 a;       // acceleration
    public float dragUp;
    public float dragDown;

    public Vector3 drag;
    public Vector3 prev;       // previous position
    Vector3 temp;       // temporal position
    public GameObject sph;     // game object for the particle

    // Start is called before the first frame update
    void Start()
    {
        sph = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sph.transform.position = p;
        sph.transform.localScale = new Vector3(r * 2, r * 2, r * 2);
        float cr = Random.Range(0.0f, 1.0f);
        float cg = Random.Range(0.0f, 1.0f);
        float cb = Random.Range(0.0f, 1.0f);
        color = new Color(cr, cg, cb);
        sph.GetComponent<MeshRenderer>().material.SetColor("_Color", color);
        prev = p;
        a = Vector3.zero;
        drag.y = 1;
    }

    void Verlet(float dt)
    {
        temp = p;                           // save p temporarily
        a = forces / mass;                  // a = F/m
        p = 2 * p - prev + (a * dt * dt);   // Verlet
        prev = temp;                        // restore previous position
        sph.transform.position = p;
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.frameCount > 20)
        {
            forces.y += -g * mass * Time.deltaTime;
            if (p.y > prev.y) drag = -forces * dragUp;
            else if (p.y < prev.y) drag = -forces * dragDown;
            else drag = Vector3.zero;
            forces += drag;
            CheckFloor();
            Verlet(Time.deltaTime);
        }
    }

    void CheckFloor()
    {
        if(p.y < r)
        {
            forces.y = -forces.y * rc;
            //Debug.Log("F=" + forces.ToString("F5"));
            float diff = prev.y - p.y;
            p.y = r;
            prev.y = r - diff;
        }
    }

    public bool CheckCollision(Particle other)
    {
        float dx = other.p.x - p.x;
        float dy = other.p.y - p.y;
        float dz = other.p.z - p.z;

        float sumR = other.r + r;
        sumR *= sumR;

        return sumR > (dx * dx + dy * dy + dz * dz);
    }
}
