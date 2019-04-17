using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ColliderChk : MonoBehaviour
{
    private void OnCollisionEnter(Collision coll)
    {        
        switch (coll.gameObject.layer)
        {
            case 12:   //12번은 Player
                {        
                    //플레이어 체력감소
                    GameManager.instance.playerHp -= ZombieProcess.instance.atkPower;                    

                    //에너지바 추가
                    GameManager.instance.playerEnergyBar.GetComponent<EnergyBar>().
                            SetValueMax(GameManager.instance.playerMaxHp);
                    GameManager.instance.playerEnergyBar.GetComponent<EnergyBar>().
                             SetValueMin(0);
                    GameManager.instance.playerEnergyBar.GetComponent<EnergyBar>().
                              SetValueCurrent(GameManager.instance.playerHp);

                    //플레이어 상태변화
                    PlayerState.instance.playerState = PlayerState.PLAYERSTATE.DAMAGE;

                    //좀비 어택사운드
                    SoundManager.instance.PlaySfx(transform.position,
                          SoundManager.instance.handAtk,
                          0,
                          SoundManager.instance.sfxVolum);
                }
                break;
        }
    }
}
