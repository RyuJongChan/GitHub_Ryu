using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartSceneWayPointSnd : MonoBehaviour
{
    private void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "Player")
        {
            StartSceneSound.instance.PlaySfx(this.transform.position, StartSceneSound.instance.zombieAtk, 0, StartSceneSound.instance.sfxVolum);

            StartScenePlayer.instance.StepDelay = 0.3f;
        }
    }
}
