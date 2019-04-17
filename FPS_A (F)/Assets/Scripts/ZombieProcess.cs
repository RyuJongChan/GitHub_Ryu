using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ZombieProcess : MonoBehaviour
{
    public static ZombieProcess instance;

    public enum ZOMBIESTATE
    {
        IDLE = 0,
        MOVE,
        ATTACK,
        DAMAGE,
        DEAD
    }

    public ZOMBIESTATE zombieState = ZOMBIESTATE.IDLE;

    Vector3 currentVelocty;  //현재 위치

    float gravity = 10.0f;

    public int maxHp = 0;   
    public int hp = 0;   
    public float speed = 0f;
    public float nightSpeed = 0f;
    public float rotSpeed = 0f;
    public float attackbleRange = 0f;  //공격 유효 범위
    public float traceRange = 0f;  //추적 유효 범위
    public float temptraceRange = 0f;
    public int atkPower;

    CharacterController cc;
    Transform target;  //플레이어     
    Animator _ani;  

    bool isAtkObj = false; 
    bool isAtkSnd = false;
    bool isDeadSnd = false;

    //웨이포인트 학습
    Vector3 enemyOrigin;
    SWS.PathManager path;

    int currentStage;

    public GameObject atk;

    void Awake()
    {
        instance = this;        
        _ani = GetComponent<Animator>();
        cc = GetComponent<CharacterController>();
        target = GameObject.FindGameObjectWithTag("Player").transform;
        zombieState = ZOMBIESTATE.IDLE;

        //웨이포인트
        enemyOrigin = transform.position;  // 현재 위치 기억
        path = Instantiate(EnemyPathManager.instance.enemyPath[0]); //원하는 웨이포인트 생성
        this.GetComponent<SWS.splineMove>().pathContainer = path;  //웨이포인트 연결       
    }

    // Use this for initialization
    void Start ()
    {
        path.transform.position = new Vector3(transform.position.x, path.transform.position.y,
                                    transform.position.z);

        currentStage = CryptoPlayerPrefs.GetInt("currentStage");
        CryptoPlayerPrefs.SetInt("currentStage", currentStage); //현재층 업데이트

        MonsterAwake(currentStage);

        //델리게이트 적용
        this.GetComponent<SWS.splineMove>().events[0].AddListener(
                       delegate { EnemyManager.instance.PauseToResume(gameObject  );    }  );

        this.GetComponent<SWS.splineMove>().events[1].AddListener(
               delegate { EnemyManager.instance.PauseToResume(gameObject); });

        this.GetComponent<SWS.splineMove>().events[2].AddListener(
               delegate { EnemyManager.instance.PauseToResume(gameObject); });
    }

    //상태 초기화 (추적을 포기하고 초기위치로 복귀할때 호출
    //웨이포인트용
    void MonsterAwake(int curstage)
    {
        maxHp = 10 + (curstage * 2);
        speed = 1.0f + curstage;
        nightSpeed = speed * 2;
        rotSpeed = 10.0f;
        attackbleRange = 2.2f;  //공격 유효 범위
        traceRange = 7.0f;  //추적 유효 범위
        temptraceRange = traceRange * 10.0f;
        atkPower = 9 + curstage;

        _ani.SetBool("isIdle", true);
        _ani.SetBool("isAttack", false);
        _ani.SetBool("isRun", false);
        _ani.SetBool("isWalk", false);

        transform.position = enemyOrigin;
        this.GetComponent<SWS.splineMove>().StartMove();  //웨이포인트 시작

        hp = maxHp;  // 체력 초기화
    }
  
	// Update is called once per frame
	void Update ()
    {
        if (hp <= 0) zombieState = ZOMBIESTATE.DEAD;
        
        Zombie_S_And_N(GameManager.instance.isShiny);
      
        currentVelocty.y -= gravity * Time.smoothDeltaTime;
        
        cc.Move(currentVelocty * Time.smoothDeltaTime);

        switch (zombieState)
        {
            case ZOMBIESTATE.IDLE:
                {
                    float distance = Vector3.Distance(target.position, transform.position);
                    Vector3 dir = target.position - transform.position;
                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출

                    this.GetComponent<SWS.splineMove>().Resume();

                    _ani.SetBool("isIdle", false);
                    _ani.SetBool("isAttack", false);
                    _ani.SetBool("isRun", false);  
                    _ani.SetBool("isWalk", true);                   

                    if (distance < traceRange)
                    {
                        zombieState = ZOMBIESTATE.MOVE;

                        if (distance <= attackbleRange)
                        {
                            zombieState = ZOMBIESTATE.ATTACK;
                        }
                    }
                }
                break;

            case ZOMBIESTATE.MOVE:
                {
                    float distance = Vector3.Distance(target.position, transform.position);
                    Vector3 dir = target.position - transform.position;
                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출

                    this.GetComponent<SWS.splineMove>().Stop();

                    _ani.SetBool("isRun", true);
                    _ani.SetBool("isAttack", false);
                    _ani.SetBool("isWalk", false);
                    _ani.SetBool("isIdle", false);                    

                    cc.SimpleMove(dir * speed);                   

                    //회전용 선형 보간 함수
                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                            rotSpeed * Time.deltaTime);

                    if (distance > traceRange || distance > temptraceRange) //타겟이 추적유효범위를 벗어나면
                    {
                        zombieState = ZOMBIESTATE.IDLE;

                        MonsterAwake(currentStage);  //위치 초기화
                    }

                    else if (distance < attackbleRange)
                    {
                        zombieState = ZOMBIESTATE.ATTACK;
                    }
                }
                break;

            case ZOMBIESTATE.ATTACK:
                {
                    float distance = Vector3.Distance(target.position, transform.position);
                    Vector3 dir = target.position - transform.position;
                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출

                    this.GetComponent<SWS.splineMove>().Stop();
                    
                    _ani.SetBool("isAttack", true);
                    _ani.SetBool("isRun", false);
                    _ani.SetBool("isWalk", false);
                    _ani.SetBool("isIdle", false);                

                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                            rotSpeed * Time.deltaTime);                  

                    if (distance > attackbleRange)
                    {
                        zombieState = ZOMBIESTATE.MOVE;
                    }                                 

                    StartCoroutine(ZombieSfx());  //하울링 효과음
                }
                break;

            case ZOMBIESTATE.DAMAGE:
                {
                    float distance = Vector3.Distance(target.position, transform.position);
                    Vector3 dir = target.position - transform.position;
                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출

                    this.GetComponent<SWS.splineMove>().Stop();
                                      
                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                            rotSpeed * Time.deltaTime);
                                 
                    if (distance < temptraceRange)
                    {                                                                                            
                        cc.SimpleMove(dir * speed);                                              
                    }
                    if (distance <= attackbleRange)
                    {
                        zombieState = ZOMBIESTATE.ATTACK;
                    }

                    if(distance > temptraceRange)
                    {
                        zombieState = ZOMBIESTATE.IDLE;
                    }
                }
                break;

            case ZOMBIESTATE.DEAD:
                {
                    StartCoroutine(ZombieDeadSfx()); //좀비Dead 사운드     

                    Instantiate(ParticleManager.instance.deadEffect,
                                                   transform.position, transform.rotation);
                    Destroy(this.gameObject);                  

                    ++EnemyManager.instance.killCnt;  //킬수체크                  

                    //킬수뷰 업데이트
                    EnemyManager.instance.enemyKillBar.GetComponent<EnergyBar>().
                         SetValueCurrent(EnemyManager.instance.maxSpawnCnt -
                                                EnemyManager.instance.killCnt);                 
                                   
                    //플레이어에게 코인, 경험치 부여
                    GameManager.instance.Exp_Cal(Random.Range(EnemyManager.instance.enemysExp[0], EnemyManager.instance.enemysExp[2]));
                    GameManager.instance.Coin_Add();                  
                }
                break;
        }
    }

    void isAtkToRun()
    {
        float distance = Vector3.Distance(target.position, transform.position);

        if (distance > attackbleRange)
        {
            atk.SetActive(false);
            zombieState = ZOMBIESTATE.MOVE;
        }
    }

    void EnemyDamage()
    {
        this.GetComponent<SWS.splineMove>().Pause();
        hp -= GameManager.instance.playerAllpower;              
        
        _ani.SetTrigger("hit");
        Invoke("IdleState", 0.1f);       

        SoundManager.instance.PlaySfx(transform.position,
                                      SoundManager.instance.bloodStabHit, 0,
                                      SoundManager.instance.sfxVolum);
        
        zombieState = ZOMBIESTATE.DAMAGE;
    }

    void IdleState()
    {         
        _ani.SetBool("isIdle", true);
        _ani.SetBool("isAttack", false);
        _ani.SetBool("isRun", false);
        _ani.SetBool("isWalk", false);    

        Invoke("ToResume", 0.1f);
    }

    void atk_On_False()
    {
        if (_ani.GetBool("isAttak"))
        {
            atk.SetActive(true);
        }
        else { atk.SetActive(false); }
    }

    void ToResume()
    {
        if (_ani.GetBool("isIdle"))
        {
            float distance = Vector3.Distance(target.position, transform.position);
            Vector3 dir = target.position - transform.position;
            dir.y = 0;
            dir.Normalize();  //거리 평준화 함수 호출

            if (distance < temptraceRange)
            {
                
                _ani.SetBool("isIdle", false);
                _ani.SetBool("isAttack", false);
                _ani.SetBool("isRun", true);
                _ani.SetBool("isWalk", false);

                cc.SimpleMove(dir * speed);                            
            }

            if (distance <= attackbleRange)
            {
                _ani.SetBool("isIdle", false);
                _ani.SetBool("isAttack", false);
                _ani.SetBool("isRun", true);
                _ani.SetBool("isWalk", false);
                zombieState = ZOMBIESTATE.ATTACK;
            }                     
        }
    }
    
    public void EnemyInfo()
    {
        //하나의 에너지바를 공통으로 사용할때
        EnemyManager.instance.enemyHpBar.GetComponent<EnergyBar>().SetValueMax(maxHp);
        EnemyManager.instance.enemyHpBar.GetComponent<EnergyBar>().SetValueMin(0);
        EnemyManager.instance.enemyHpBar.GetComponent<EnergyBar>().SetValueCurrent(hp);      
    }

    //좀비 하울링소리
    IEnumerator ZombieSfx()
    {
        if ( ! isAtkSnd)
        {
            isAtkSnd = true;
            SoundManager.instance.PlaySfx(transform.position,
                SoundManager.instance.zombieAtk, 0,
                SoundManager.instance.sfxVolum);

            yield return new WaitForSeconds(2.0f);
            isAtkSnd = false;
        }
    }

    //시체 폭파음 소리
    IEnumerator ZombieDeadSfx()
    {
        if ( ! isDeadSnd)
        {
            isDeadSnd = true;
            SoundManager.instance.PlaySfx(transform.position,
                SoundManager.instance.bloodDeath, 0,
                SoundManager.instance.sfxVolum);

            yield return new WaitForSeconds(2.0f);
            isDeadSnd = false;
        }
    }

    private void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "Gr")
        {
            hp -= 100;
        }
    }

    void OnCollisionEnter(Collision coll)
    {
        int collisionLayer = coll.gameObject.layer;

        float groundtime = 0;
        groundtime += Time.deltaTime;

        if (collisionLayer == LayerMask.NameToLayer("Ground"))
        {
            groundtime += Time.deltaTime;
            if (groundtime >= 10.0f)
            {
                Destroy(gameObject);  //자기 자신
                groundtime = 0;
            }
        }
    }

    void Zombie_S_And_N(bool Shiny)
    {
        if (Shiny)
        {
            speed = nightSpeed/2;           
            traceRange = 7.0f;            
        }

        else if(!Shiny)
        {
            speed = nightSpeed;
            traceRange = 14.0f;          
        }
    }   
}