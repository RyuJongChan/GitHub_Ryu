using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EmptyBullet : MonoBehaviour
{
    float rotSpeed = 200.0f;
    
    Rigidbody emptyri;
  
    // Start is called before the first frame update
    void Start()
    {
        int ran = Random.Range(0, 360);

        emptyri = GetComponent<Rigidbody>();
        emptyri.AddForce(transform.right * rotSpeed);

        this.transform.rotation = Quaternion.Euler(ran, 0, 0);
        Destroy(this.gameObject, 1.5f);
    }
}