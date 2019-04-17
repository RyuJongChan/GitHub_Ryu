using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartSceneZombie : MonoBehaviour
{
    public GameObject SZB;

    enum ZOMBIE_Boss_State
    {
        IDLE = 0,
        MOVE,
        ATTACK,        
        DEAD
    }

    ZOMBIE_Boss_State BossState = ZOMBIE_Boss_State.IDLE;

    float Boss_gravity = 10.0f;
    
    public float Boss_speed = 10.0f;
    public float Boss_rotSpeed = 10.0f;
    public float Boss_attackbleRange = 20.0f;  //공격 유효 범위
    public float Boss_traceRange = 30.0f;     //추적 유효 범위

    Animator Boss_ani;

    Vector3 bornPositon = Vector3.zero;

    Quaternion bornRotation;

    bool Boss_isAtk = false;

    void Awake()
    {
        Boss_ani = GetComponent<Animator>();
        BossState = ZOMBIE_Boss_State.IDLE;       
    }

    // Use this for initialization
    void Start()
    {
        BossAwake();
        bornRotation = new Quaternion(this.transform.rotation.x, this.transform.rotation.y, this.transform.rotation.z, this.transform.rotation.w );       
    }

    void BossAwake()
    {
        Boss_ani.SetBool("isIdle", true);
        Boss_ani.SetBool("isRun", false);
        Boss_ani.SetBool("isAttack", false);
        Boss_ani.SetBool("isDead", false);       
    }

    // Update is called once per frame
    void Update()
    {        
        switch (BossState)
        {
            case ZOMBIE_Boss_State.IDLE:
                {
                    Boss_ani.SetBool("isIdle", true);
                    Boss_ani.SetBool("isRun", false);
                    Boss_ani.SetBool("isAttack", false);

                    float distance = Vector3.Distance(StartScenePlayer.instance.player.position, this.transform.position);

                    if (distance <= Boss_traceRange)
                    {
                        BossState = ZOMBIE_Boss_State.MOVE;

                        if (distance <= Boss_attackbleRange)
                        {
                            BossState = ZOMBIE_Boss_State.ATTACK;
                        }
                    }
                }
                break;

            case ZOMBIE_Boss_State.MOVE:
                {
                    Boss_ani.SetBool("isIdle", false);
                    Boss_ani.SetBool("isRun", false);
                    Boss_ani.SetBool("isAttack", true);

                    float distance = Vector3.Distance(StartScenePlayer.instance.player.position, transform.position);
                    Vector3 dir = StartScenePlayer.instance.player.position - transform.position;

                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출                  

                    //회전용 선형 보간 함수
                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                         Boss_rotSpeed * Time.deltaTime);                   

                    if (distance > Boss_traceRange) 
                    {
                        this.transform.rotation = bornRotation;
                        BossState = ZOMBIE_Boss_State.IDLE;
                    }

                    if (distance <= Boss_attackbleRange)
                    {                      
                        BossState = ZOMBIE_Boss_State.ATTACK;
                    }

                }
                break;

            case ZOMBIE_Boss_State.ATTACK:
                {
                    Boss_ani.SetBool("isAttack", true);
                    Boss_ani.SetBool("isRun", false);
                    Boss_ani.SetBool("isIdle", false);

                    float distance = Vector3.Distance(StartScenePlayer.instance.player.position, transform.position);
                    Vector3 dir = StartScenePlayer.instance.player.position - transform.position;

                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출


                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                            Boss_rotSpeed * Time.deltaTime);

                  

                    if (distance > Boss_attackbleRange)
                    {
                        this.transform.rotation = bornRotation;
                        BossState = ZOMBIE_Boss_State.MOVE;

                        if (distance > Boss_traceRange)
                        {
                            this.transform.rotation = bornRotation;
                            BossState = ZOMBIE_Boss_State.IDLE;                           
                        }
                    }
                }
                break;

            case ZOMBIE_Boss_State.DEAD:
                {
                    Boss_ani.SetBool("isAttack", false);
                    Boss_ani.SetBool("isRun", false);
                    Boss_ani.SetBool("isIdle", false);
                    Boss_ani.SetBool("isDead", true);
                }
                break;
        }
    }  
}