using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowSpwanPoint : MonoBehaviour
{
    Transform tr;

	// Use this for initialization
	void Start ()
    {
        tr = transform;
	}
	
	// Update is called once per frame
	void Update ()
    {
        tr.position = GameController.instance.muzzleSpawnPoint.position;
        tr.rotation = GameController.instance.muzzleSpawnPoint.rotation;
    }
}
