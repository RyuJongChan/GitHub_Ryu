using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ZombieBoss : MonoBehaviour
{
    enum ZOMBIEBossState
    {
        IDLE = 0,
        MOVE,
        ATTACK,         
        DEAD
    }

    ZOMBIEBossState BossState = ZOMBIEBossState.IDLE;

    float Bossgravity = 10.0f;

    public int Bosshp;
    public int BossmaxHp = 0;
    public float BossSpeed = 0;
    public float BossrotSpeed = 0;
    public float BossAttackbleRange = 0;  
    public float BossTraceRange = 0;     

    Animator _Bossani;

    public GameObject BossAtkObj;
    bool BossisAtk = false;

    void Awake()
    {
        _Bossani = GetComponent<Animator>();
        BossState = ZOMBIEBossState.IDLE;
        BossAwake();
    }  

    void BossAwake()
    {
        BossmaxHp = 50;
        BossSpeed = 10.0f;
        BossrotSpeed = 10.0f;
        BossAttackbleRange = 5.0f;  //공격 유효 범위
        BossTraceRange = 15.0f;     //추적 유효 범위

        _Bossani.SetBool("isIdle", true);
        _Bossani.SetBool("isRun", false);
        _Bossani.SetBool("isAttack", false);
        _Bossani.SetBool("isDead", false);

        Bosshp = BossmaxHp;  // 체력 초기화
    }

    // Update is called once per frame
    void Update()
    {
        if (Bosshp <= 0) BossState = ZOMBIEBossState.DEAD;

        switch (BossState)
        {
            case ZOMBIEBossState.IDLE:
                {
                    _Bossani.SetBool("isIdle", true);
                    _Bossani.SetBool("isRun", false);
                    _Bossani.SetBool("isAttack", false);

                    float distance = Vector3.Distance(GameController.instance.player.position, this.transform.position);

                    if (distance <= BossTraceRange)
                    {
                        BossState = ZOMBIEBossState.MOVE;

                        if (distance <= BossAttackbleRange)
                        {
                            BossState = ZOMBIEBossState.ATTACK;
                        }
                    }
                }
                break;

            case ZOMBIEBossState.MOVE:
                {
                    _Bossani.SetBool("isIdle", false);
                    _Bossani.SetBool("isRun", true);
                    _Bossani.SetBool("isAttack", false);

                    float distance = Vector3.Distance(GameController.instance.player.position, transform.position);
                    Vector3 dir = GameController.instance.player.position - transform.position;

                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출                  

                    //회전용 선형 보간 함수
                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                         BossrotSpeed * Time.deltaTime);

                    if (distance > BossTraceRange) //타겟이 추적유효범위를 벗어나면
                    {
                        BossState = ZOMBIEBossState.IDLE;
                    }

                    if (distance <= BossAttackbleRange)
                    {
                        BossState = ZOMBIEBossState.ATTACK;
                    }
                }
                break;

            case ZOMBIEBossState.ATTACK:
                {
                    _Bossani.SetBool("isAttack", true);
                    _Bossani.SetBool("isRun", false);
                    _Bossani.SetBool("isIdle", false);

                    float distance = Vector3.Distance(GameController.instance.player.position, transform.position);
                    Vector3 dir = GameController.instance.player.position - transform.position;

                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출


                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                            BossrotSpeed * Time.deltaTime);

                    StartCoroutine(Boss_Fire());  //공격모션        


                    if (distance > BossAttackbleRange)
                    {
                        BossState = ZOMBIEBossState.MOVE;

                        if (distance > BossTraceRange)
                        {
                            BossState = ZOMBIEBossState.IDLE;
                        }
                    }
                }
                break;
          
            case ZOMBIEBossState.DEAD:
                {
                    _Bossani.SetBool("isAttack", false);
                    _Bossani.SetBool("isRun", false);
                    _Bossani.SetBool("isIdle", false);
                    _Bossani.SetBool("isDead", true);

                    GameManager.instance.Exp_Cal(Random.Range(EnemyManager.instance.enemysExp[0]*5, EnemyManager.instance.enemysExp[2]*5));
                    GameManager.instance.Coin_Add();

                    Destroy(this.gameObject, 3.0f);
                }
                break;
        }
    }   
   
    void EnemyDamage()
    {
        Bosshp -= GameManager.instance.playerAllpower;       

        SoundManager.instance.PlaySfx(transform.position,
                                      SoundManager.instance.bloodStabHit, 0,
                                      SoundManager.instance.sfxVolum);
    }

    //좀비 발사체 생성
    IEnumerator Boss_Fire()
    {
        if (PlayerState.instance.playerState == PlayerState.PLAYERSTATE.DEAD)
        {
            BossisAtk = true;
            BossAtkObj.SetActive(false);
        }

        else if (!BossisAtk)
        {
            BossisAtk = true;
           
            BossAtkObj.SetActive(true);
            
            yield return new WaitForSeconds(1.3f);

            BossAtkObj.SetActive(false);
            BossisAtk = false;
        }
    }

    private void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "Gr")
        {
            Bosshp -= 100;
        }
    }
}
