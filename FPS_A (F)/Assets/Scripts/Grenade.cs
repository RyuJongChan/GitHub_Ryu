using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grenade : MonoBehaviour
{
    public static Grenade instance;

    [HideInInspector]
    public float grPower = 50.0f;
     
    Rigidbody grri;

    float greTime;

    bool isGr = false;

    private void Awake()
    {
        instance = this;
    }

    // Start is called before the first frame update
    void Start()
    {
        grri = GetComponent<Rigidbody>();
       
        grri.AddForce(-transform.forward * grPower);        
        
        SoundManager.instance.PlaySfx(transform.position,
                              SoundManager.instance.grSnd, 1.8f,
                              1.0f);

        Destroy(this.gameObject, 2.0f);        
    }

    //Update is called once per frame
    void Update()
    {      
        if (!isGr)
        {
            greTime += Time.deltaTime;            
            
            if (greTime >= 1.8f)
            {                
                GameObject obj;
                obj = Instantiate(ParticleManager.instance.grEffect, this.transform.position, this.transform.rotation);
                isGr = true;
                Destroy(obj, 1.0f);                        
            }
        }
    }   
}
