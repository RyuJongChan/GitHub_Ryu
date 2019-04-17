using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LastBoss : MonoBehaviour
{
    public static LastBoss instance;

    public enum Last_Boss_State
    {
        IDLE = 0,
        MOVE,        
        DEAD
    }

    public Last_Boss_State LBossState = Last_Boss_State.IDLE;

    float LBossgravity = 10.0f;
    public int LBosshp;
    public int LBossmaxHp = 50;
    public float LBossspeed = 10.0f;
    public float LBossrotSpeed = 10.0f;
    public float LBossattackbleRange = 20.0f;  //공격 유효 범위
    public float LBosstraceRange = 50.0f;     //추적 유효 범위
    public float LbossAttTime;
    public float LbossMovTime;
    public int LbossAttpower;

    Animator _LBossani;
   
    public GameObject LBossAtkArea;
    public GameObject Lboss; 

    bool LBossisAtk = false;
    bool isTel = false;

    void Awake()
    {
        instance = this;
        _LBossani = GetComponent<Animator>();
        LBossState = Last_Boss_State.IDLE;
    }

    // Use this for initialization
    void Start()
    {
        LBossAwake();
    }

    void LBossAwake()
    {
        _LBossani.SetBool("isIdle", true);
        _LBossani.SetBool("isMove", false);       
        _LBossani.SetBool("isDead", false);

        LBossmaxHp = 50;
        LbossAttpower = 50;

        LBosshp = LBossmaxHp;  // 체력 초기화
    }

    // Update is called once per frame
    void Update()
    {
        LBoss_Gravity();

        if (LBosshp <= 0) LBossState = Last_Boss_State.DEAD;

        if (PlayerState.instance.playerState == PlayerState.PLAYERSTATE.DEAD)
        {
            Destroy(this.gameObject);
        }

        switch (LBossState)
        {
            case Last_Boss_State.IDLE:
                {
                    _LBossani.SetBool("isIdle", true);
                    _LBossani.SetBool("isMove", false);                  

                    Vector3 dir = GameController.instance.player.position - transform.position;

                    dir.y = 0;
                    dir.Normalize();  //거리 평준화 함수 호출                  

                    //회전용 선형 보간 함수
                    transform.rotation = Quaternion.Lerp(transform.rotation,
                                         Quaternion.LookRotation(dir),
                                         LBossrotSpeed * Time.deltaTime);

                    LbossAttTime += Time.deltaTime;
                    
                    if (LbossAttTime >= 2.0f)
                    {
                        ParticleManager.instance.TeleEffect.SetActive(true);

                        StartCoroutine(Lboss_Tel_Snd());                         
                    }

                    if (LbossAttTime >= 5.0f)
                    {
                        Lboss.transform.position = new Vector3(GameController.instance.player.position.x, GameController.instance.player.position.y + 5.0f, GameController.instance.player.position.z + 1.0f);
                        LBossState = Last_Boss_State.MOVE;
                        LbossAttTime = 0;
                    }
                }
                break;

            case Last_Boss_State.MOVE:
                {
                    ParticleManager.instance.TeleEffect.SetActive(false);
                    _LBossani.SetBool("isMove", true);
                    _LBossani.SetBool("isIdle", false);

                    LbossMovTime += Time.deltaTime;

                    if (LbossMovTime >= 2.0f)
                    {
                        LBossState = Last_Boss_State.IDLE;
                        LbossMovTime = 0;
                    }
                }
                break;           

            case Last_Boss_State.DEAD:
                {                   
                    _LBossani.SetBool("isMove", false);
                    _LBossani.SetBool("isIdle", false);
                    _LBossani.SetBool("isDead", true);

                    GameManager.instance.Clear = true;

                    GameManager.instance.victoryCan.SetActive(true);
                    GameManager.instance.ingameCan.SetActive(false);
                    GameManager.instance.contCan.SetActive(false);                  

                    Destroy(this.gameObject, 1.0f);
                }
                break;
        }
    }

    void EnemyDamage()
    {
        LBosshp -= GameManager.instance.playerAllpower;
        
        SoundManager.instance.PlaySfx(transform.position,
                                      SoundManager.instance.bloodStabHit, 0,
                                      SoundManager.instance.sfxVolum);
    }

    private void OnCollisionEnter(Collision coll)
    {
        if (coll.collider.tag == "Gr")
        {
            LBosshp -= 100;
        }
    }

    void LBoss_Gravity()
    {
        if (this.transform.position.y >= 0)
        {
            this.transform.position = new Vector3(this.transform.position.x, this.transform.position.y - (Time.deltaTime * 2.0f), this.transform.position.z);
        }

        if (this.transform.position.y >= -1.0f && this.transform.position.y <= 1.0f)
        {
            LBossAtkArea.SetActive(true);
        }
        else { LBossAtkArea.SetActive(false); }
    }

    IEnumerator Lboss_Tel_Snd()
    {
        if (!isTel)
        {
            isTel = true;
            SoundManager.instance.PlaySfx2(transform.position,
                SoundManager.instance.lbossSnd, 0,
                SoundManager.instance.sfxVolum);

            yield return new WaitForSeconds(3.0f);
            isTel = false;
        }
    }
}
