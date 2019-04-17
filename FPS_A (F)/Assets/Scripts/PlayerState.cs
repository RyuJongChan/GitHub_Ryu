using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerState : MonoBehaviour
{
    public static PlayerState instance;

    Transform tr;

    bool isRun = false;  //달리기 효과 코루틴 제어 플래그
    
    //FSM(유한상태기계)
    public enum PLAYERSTATE
    {
        AWAKE = 0,  //준비
        IDLE,  //대기
        MOVE,  //이동
        ATTACK,  //공격
        DAMAGE,  //피격받았을때       
        DEAD  //죽음처리  
    }

    public PLAYERSTATE playerState = PLAYERSTATE.AWAKE;

    void Awake()
    {
        tr = transform;
        instance = this;      
    }
		
	// Update is called once per frame
	void Update ()
    {
        if (GameManager.instance.playerHp <= 0) playerState = PLAYERSTATE.DEAD;      

        switch (playerState)
        {            
            case PLAYERSTATE.AWAKE:
                {
                    PlayerAwake();
                }
                break;

            case PLAYERSTATE.IDLE:
                {                   
                    if (Input.GetKey("w") || Input.GetKey("s") || Input.GetKey("a") || Input.GetKey("d"))
                    {
                        playerState = PLAYERSTATE.MOVE;
                    }

                    else if(GameController.instance.isAttack)
                    {
                        playerState = PLAYERSTATE.ATTACK;
                    }

                    else
                    {
                        playerState = PLAYERSTATE.IDLE;
                    }                    
                }
                break;

            case PLAYERSTATE.MOVE:
                {                 
                   if ( !Input.GetKey("w") && !Input.GetKey("s") && !Input.GetKey("a") && !Input.GetKey("d"))
                    {
                        playerState = PLAYERSTATE.IDLE;
                    }
                    else if (GameController.instance.isAttack)
                    {
                        playerState = PLAYERSTATE.ATTACK;
                    }                   

                    StartCoroutine(Step_Run());
                }
                break;

            case PLAYERSTATE.ATTACK:
                {
                    if (!GameManager.instance.Clear)
                    {
                        PlayerAwake();
                    }

                    else if (!GameController.instance.isAttack) playerState = PLAYERSTATE.IDLE;                                 
                }
                break;

            case PLAYERSTATE.DAMAGE:
                {
                    if (GameManager.instance.playerHp <= 0)
                    {
                        playerState = PLAYERSTATE.DEAD;
                    }                   

                    else if(GameController.instance.isAttack)
                    {
                        playerState = PLAYERSTATE.ATTACK;
                    }

                    else if(Input.GetKey("w") || Input.GetKey("s") || Input.GetKey("a") || Input.GetKey("d"))
                    {
                        playerState = PLAYERSTATE.MOVE;
                    }                   

                    else
                    {
                        playerState = PLAYERSTATE.IDLE;
                    }

                    //쉐이크 동작                    
                    EZCameraShake.CameraShaker.Instance.Shake(EZCameraShake.CameraShakePresets.Earthquake);
                }
                break;

            case PLAYERSTATE.DEAD:
                {                                       
                    GameManager.instance.dieCan.SetActive(true);
                    GameManager.instance.ingameCan.SetActive(false);
                    GameManager.instance.contCan.SetActive(false);
                }
                break;      
        }
	}

    public void PlayerAwake()
    {
        playerState = PLAYERSTATE.IDLE;
    }

    public void Player_Moving()
    {
        playerState = PLAYERSTATE.MOVE;
    }

    IEnumerator Step_Run()
    {
        if (!isRun)
        {
            isRun = true;

            yield return new WaitForSeconds(0.3f);

            AudioClip[] rndAudio = {SoundManager.instance.step_A,
                     SoundManager.instance.step_B, SoundManager.instance.step_C};

            SoundManager.instance.PlaySfx(tr.position, rndAudio[Random.Range(0, 2)],
                       0, SoundManager.instance.VolumUp);

            isRun = false;
        }
    }   
}
