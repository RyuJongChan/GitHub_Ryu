using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LbossAtk : MonoBehaviour
{
    private void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "Player")
        {
            GameManager.instance.playerHp -= LastBoss.instance.LbossAttpower;
            print(GameManager.instance.playerHp);
            PlayerState.instance.playerState = PlayerState.PLAYERSTATE.DAMAGE;
        }
    }
}
