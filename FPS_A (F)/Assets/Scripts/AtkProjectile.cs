using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AtkProjectile : MonoBehaviour
{
    private void OnTriggerEnter(Collider coll)
    {
        switch (coll.tag)
        {
            case "Player":
                {
                    //플레이어 체력 감소
                    GameManager.instance.playerHp -= 20;

                    //플레이어 상태 변화
                    PlayerState.instance.playerState = PlayerState.PLAYERSTATE.DAMAGE;
                }
                break;
        }      
    }
}
