using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameController : MonoBehaviour
{   
    public static GameController instance; 
       
    public Transform  Bullet;    
    public Transform  player;
    public Transform  mainCam;  
    public Transform  spawnPoint;
    public Transform  EmptyBulletPoint;
    public Transform  muzzleSpawnPoint;
    public GameObject useGun;   
    public GameObject Grenade;
    public GameObject EmptyBullet;
    public GameObject[] Gun_ = new GameObject[4];
    public GameObject[] Aim_;   
    
    Vector2[] InitAimpos_ = new Vector2[4];

    //에임 거리 관련
    RectTransform[] rt = new RectTransform[4];  //에임 상하/좌우 거리
    public float aimWidthX;
    float maxAimarea = 30.0f;
    
    bool isFire = false;  //총알 생성 제어 플래그(코루틴용)
    public bool isAttack = false;
    public bool isShoot  = false;  

    public Vector3 spPos = Vector3.zero;
    public Vector3 originSppos = Vector3.zero;
    public Vector3 originUsgun = Vector3.zero;
 
    public float bulletAngle;   

    void Awake()
    {
        instance = this;
        bulletAngle = 0.1f;
        originSppos = spawnPoint.localPosition;       

        for (int i = 0; i <= 3; i++)
        {
            rt[i] = Aim_[i].GetComponent<RectTransform>();
            InitAimpos_[i] = rt[i].anchoredPosition;
        }
    }
  
    // Update is called once per frame
    void Update ()
    {
        Search_Enemy();
        Aim_Return();       
        Player_Gravity();
        
        aimWidthX  = Vector3.Distance(rt[2].position, rt[3].position);
       
        if (isShoot)
        {
            StartCoroutine(BulletInit());            
        }     

        else 
        {
            spawnPoint.localPosition = originSppos;          
        }
    }
    
    //총알 생성
    IEnumerator BulletInit()
    {
        if(!isFire && !GameManager.instance.Clear && PlayerState.instance.playerState != PlayerState.PLAYERSTATE.DEAD)
        {
            isFire = true;      //플레이어 상태 변화 연속 수행 방지
            isAttack = true;    //총알 생성 연속 수행 방지
            
            spPos = spawnPoint.position;
            
            Instantiate(Bullet, spawnPoint.position, mainCam.transform.rotation);

            if (GameManager.instance.ZoomNum == 0)
            {               
                StartCoroutine(MainCam_Shake(GameManager.instance.Gun_BoundAndFirespeed, GameManager.instance.Gun_BoundAndFirespeed / 2));
            }
            else if (GameManager.instance.ZoomNum == 1)
            {               
                StartCoroutine(MainCam_Shake(GameManager.instance.Gun_BoundAndFirespeed / 2, GameManager.instance.Gun_BoundAndFirespeed / 3));
            }

            Bullet_Bound(0.2f);

            SoundManager.instance.PlaySfx(transform.position,
                               SoundManager.instance.fireSnd, 0f,
                               SoundManager.instance.gunVolum);

            Aim_Bound  (GameManager.instance.Gun_BoundAndFirespeed);
            
            Instantiate(EmptyBullet, EmptyBulletPoint.transform.position, EmptyBulletPoint.rotation);

            Muzzle_Effect(); 
            yield return new WaitForSeconds(GameManager.instance.Gun_BoundAndFirespeed);
            
            isFire = false;  
            isAttack = false;
        }        
    }

    public IEnumerator MainCam_Shake(float _amount, float _duration)
    {
        float timer = 0;
        timer += Time.deltaTime;
        while (timer <= _duration)
        {
            timer += Time.deltaTime;
            GameManager.instance.MainCam.transform.localPosition = (Vector3)Random.insideUnitCircle * _amount + GameManager.instance.originMainCamPos;
            
            yield return null;
        }
        GameManager.instance.MainCam.transform.localPosition = GameManager.instance.originMainCamPos;
    }

    //머즐 이펙트
    void Muzzle_Effect()
    {       
        GameObject obj = Instantiate(ParticleManager.instance.muzzleImpact);

        obj.transform.position =  muzzleSpawnPoint.transform.position;
        obj.transform.rotation =  muzzleSpawnPoint.transform.rotation;

        Destroy(obj, 0.2f);      
    } 

    void Search_Enemy()
    {            
        RaycastHit hit;

        if(Physics.Raycast(spawnPoint.position,    spawnPoint.up,   out  hit,   45 ))
        {
            if (hit.transform.gameObject.layer == LayerMask.NameToLayer("Enemy"))
            {   
                EnemyManager.instance.enemyHpBar.SetActive(true);
                EnemyManager.instance.enemyHpBar.GetComponent<EnergyBarToolkit.EnergyBarFollowObject>().
                           followObject = hit.transform.gameObject;

                hit.transform.SendMessage("EnemyInfo", SendMessageOptions.DontRequireReceiver);
            }
            else
            {
                EnemyManager.instance.enemyHpBar.SetActive(false);
            }
        }
    }


    private void OnTriggerEnter(Collider coll)
    {       
        if (coll.tag == "LbossAtk")
        {
            print(1);
        }
    }

    public void Aim_Bound(float boundspeed)
    {      
        for (int i = 0; i <= 3; i++)
        {
            Vector2 udlr;

            if (i == 1 || i == 2) maxAimarea = -maxAimarea;                                  

            Vector2 aimx = new Vector2(InitAimpos_[i].x + maxAimarea, InitAimpos_[i].y);
            Vector2 aimy = new Vector2(InitAimpos_[i].x             , InitAimpos_[i].y + maxAimarea);
            
            if (i == 0 || i == 1) udlr = aimy;
            else udlr = aimx;

            Aim_[i].transform.localPosition = Vector2.Lerp(Aim_[i].transform.localPosition, udlr, boundspeed);

            if (i == 1 || i == 2) maxAimarea = -maxAimarea;
        }      
    }

    void Bullet_Bound(float boundSize)
    {
        if (aimWidthX <= 60.0f)
        {
            float tempx = Random.Range(originSppos.x - boundSize, originSppos.x + boundSize);
            float tempy = Random.Range(originSppos.y - boundSize, originSppos.y + boundSize);

            spawnPoint.localPosition = new Vector3(tempx, tempy, spawnPoint.localPosition.z);
        }

        else if (aimWidthX > 60.0f)
        {
            float tempx = Random.Range((originSppos.x - boundSize * 2), (originSppos.x + boundSize * 2));
            float tempy = Random.Range((originSppos.y - boundSize * 2), (originSppos.y + boundSize * 2));

            spawnPoint.localPosition = new Vector3(tempx, tempy, spawnPoint.localPosition.z);
        }
    }

    void Aim_Return()
    {
        if (isFire == false)
        {
            for (int i = 0; i <= 3; i++)
            {
                Aim_[i].transform.localPosition = Vector2.Lerp(Aim_[i].transform.localPosition, InitAimpos_[i], Time.deltaTime * 3.0f);
            }                     
        }
    }  
    
    void Player_Gravity()
    {
        if (player.transform.position.y >= 1.81)
        {            
            player.transform.position = new Vector3(player.transform.position.x, player.transform.position.y - (Time.deltaTime * 2.0f), player.transform.position.z);
            Aim_Bound(10.0f);
        }
    }
}
