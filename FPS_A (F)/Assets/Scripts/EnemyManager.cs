using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyManager : MonoBehaviour
{
    public static EnemyManager instance;

    public GameObject enemy;
    public GameObject lastBoss;

    bool isSpawn = false;  //코루틴 제어 플래그
    int lastbossNum = 1;    
    public float spawnTime = 0;  //리젠시간
    int spwanCnt = 0;
    public int maxSpawnCnt = 0; //총 적 스폰 갯수
    public int killCnt = 0;

    public GameObject enemyHpBar;
    public GameObject enemyKillBar;  //몬스터 킬숫자 뷰

    // 몬스터 경험치
    public float[] enemysExp;  //적경험치 관리자

    //몬스터 코인 획득 정보
    public int[] enemyCoinAmount; 

    private void Awake()
    {
        instance = this;

        spawnTime = 2.0f;  //리젠시간
        spwanCnt = 0;
        maxSpawnCnt = 5; //총 적 스폰 갯수
    }

    // Use this for initialization
    void Start ()
    {
        //적킬수
        enemyKillBar.GetComponent<EnergyBar>().SetValueMin(0);
        enemyKillBar.GetComponent<EnergyBar>().SetValueMax(maxSpawnCnt);
    }
	
	// Update is called once per frame
	void Update ()
    {
        LastBoss_Appearance();
        if (spwanCnt >= maxSpawnCnt) return;
           
        StartCoroutine(EnemySpawn());        
	}

    //일반 좀비 생성 프로세스
    IEnumerator EnemySpawn()
    {
        if (!isSpawn)
        {
            isSpawn = true;
            yield return new WaitForSeconds(spawnTime);

            GameObject enemyObj = Instantiate(enemy);                    
            float x = Random.Range(  5.5f, 13.0f);  //좌우측 
            float z = Random.Range(-12.0f, -2.0f);  //전후방 
            enemyObj.transform.position = new Vector3(x, 1.0f, z);
            ++spwanCnt;  //스폰갯수 증가 체크
            enemyObj.name = "Enemy_" + spwanCnt;
            
            isSpawn = false;            
        }
    }

    //라스트 보스 생성함수
    void LastBoss_Appearance()
    {       
        if ((killCnt >= maxSpawnCnt) && (lastbossNum == 1))
        {            
            lastBoss.SetActive(true);           
            lastbossNum = 0;
        }
    }

   public void PauseToResume( GameObject obj  )
    {      
        obj.GetComponent<SWS.splineMove>().Pause();

        StartCoroutine(ResumeToPause(1.0f, obj ));

        obj.GetComponent<Animator>().SetBool("isIdle", true);
        obj.GetComponent<Animator>().SetBool("isWalk", false);
    }

    IEnumerator   ResumeToPause(float time, GameObject obj  )
    {
        yield return new WaitForSeconds(time);

        try
        {
            obj.GetComponent<SWS.splineMove>().Resume();
            //걷기 모션
            obj.GetComponent<Animator>().SetBool("isIdle", false);
            obj.GetComponent<Animator>().SetBool("isWalk", true);
        }
        catch { };
    } 
}