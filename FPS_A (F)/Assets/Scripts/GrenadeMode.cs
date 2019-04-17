using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GrenadeMode : MonoBehaviour
{
    public static GrenadeMode instance;
  
    public GameObject GrenadeM;  
    public GameObject GrenadeMsplint;
    public GameObject TempSplint;  

    private void Awake()
    {
        instance = this;
    }   
}
